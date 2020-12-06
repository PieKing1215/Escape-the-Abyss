/**
	Floor manager.
	@file FloorManager.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "FloorManager.h"

// Engine inludes.
#include "dragonfly/DisplayManager.h"
#include "dragonfly/GameManager.h"
#include "dragonfly/LogManager.h"
#include "dragonfly/WorldManager.h"
#include "dragonfly/utility.h"

// Game includes.
#include "Floor.h"
#include "Player.h"
#include "GameOver.h"

#include "EnemySlime.h"
#include "EnemyBat.h"

FloorManager::FloorManager() {
	setType("FloorManager");
	// TODO: set this based on save file read.
	currentFloor = 0;
	floorSize = 5;
	noise = 80;
	previousEndHeight = 0;
	player = NULL;
	nextCheckpoint = NULL;
	currentCheckpoint = NULL;
	worldHeight = 1000;
	maxLevel = 5;
}

FloorManager::FloorManager(FloorManager const&) {
	setType("FloorManager");
	// TODO: set this based on save file read.
	currentFloor = 0;
	floorSize = 5;
	noise = 10;
	previousEndHeight = 0;
	player = NULL;
	nextCheckpoint = NULL;
	currentCheckpoint = NULL;
	worldHeight = 1000;
	maxLevel = 5;
}

void FloorManager::operator=(FloorManager const&) {

}

FloorManager& FloorManager::getInstance() {
	static FloorManager floorManager;
	return floorManager;
}

int FloorManager::startUp() {
	df::Manager::startUp();
	if (FloorManager::nextFloor()) {
		shutDown();
		writeLog("ERROR", "Error creating foor.");
		return -1;
	}
	return 0;
}

void FloorManager::shutDown() {
	df::Manager::shutDown();
}

int FloorManager::getFloor() const {
	return currentFloor;
}

void FloorManager::setFloor(int new_floor) {
	currentFloor = new_floor;
}

void FloorManager::setFloorSize(int new_floor_size) {
	floorSize = new_floor_size;
}

void FloorManager::setNoise(int new_noise) {
	if (new_noise > 100) {
		new_noise = 100;
	}
	else if (new_noise < 0) {
		new_noise = 0;
	}
	else {
		noise = new_noise;
	}
}

int FloorManager::nextFloor() {
	// Create floor
	srand(currentFloor + 1);
	int floorHeight = previousEndHeight, levelWidth = 100, enemyMultiplier = (((levelWidth - 15) / 100) - 5) * currentFloor, enemies = 0;
	if (enemyMultiplier <= 0) {
		enemyMultiplier = 1;
	}
	const float groundToAir = (float)(rand() % 10) / 10.0;
	const int totalEnemies = rand() % enemyMultiplier + 5;

	df::Box view = WM.getView(), boundary = WM.getBoundary();

	for (int x = 0; x < levelWidth; x++) {
		if (currentFloor == maxLevel) {
			new Floor(df::Vector((currentFloor * levelWidth) + 10.0f + x, worldHeight + 20.0f + floorHeight));
		}
		else {
			srand((currentFloor + 1) * (x + 2) * (rand() % 50));
			if (x % floorSize == 0) {
				int height = rand() % 200 - 100;
				if (abs(height) >= 100 - noise) {
					if (height >= 0 && floorHeight < 0 && worldHeight > abs(floorHeight) + 20) {
						floorHeight++;
					}
					else if (height < 0) {
						floorHeight--;
					}
				}
			}
			// simple sin wave for testing. height = (int)(sin(x / 10.0f) * 2.0f + sin(x / 3.14f) * 2.0f);
			new Floor(df::Vector((currentFloor * levelWidth) + 10.0f + x, worldHeight + 20.0f + floorHeight));

			// Check if this floor tile should have an enemy spawned above it.
			if (enemies < totalEnemies && (currentFloor > 0 && x % (levelWidth / totalEnemies) == 0) || (currentFloor == 0 && x > 25 && x % (levelWidth / totalEnemies) == 0)) {
				float tmp = (float)(rand() % 10) / 10.0;
				// TOOD: there is a big performance hit on enemy spawning but not floor spawning
				if (tmp < groundToAir) {
					EnemySlime* slime = new EnemySlime();
					slime->setPosition(df::Vector((currentFloor * levelWidth) + 10.0f + x, worldHeight + 20.0f + floorHeight - 4));
				}
				else {
					EnemyBat* bat = new EnemyBat();
					bat->setPosition(df::Vector((currentFloor * levelWidth) + 10.0f + x, worldHeight + 20.0f + floorHeight - 6));
				}
				enemies++;
			}
			else if (!player && x == 0) {
				// Make world really tall
				WM.setBoundary(df::Box(df::Vector(), 10 + levelWidth, worldHeight + view.getVertical()));
				boundary = WM.getBoundary();

				// Create the player
				player = new Player();
				player->setPosition(df::Vector(0, worldHeight));
				player->setVelocity(df::Vector(1, 0));

				// Make camera follow player
				WM.setViewFollowing(player);
				WM.setViewSlack(df::Vector(0.25, 0.25));
			}
		}
	}

	previousEndHeight = floorHeight;

	// Create checkpoint the end of the level
	currentCheckpoint = nextCheckpoint;
	nextCheckpoint = new Checkpoint(df::Vector((currentFloor * levelWidth) + (levelWidth / 2), worldHeight + 20 + floorHeight), 1, DM.getVertical(), currentFloor == maxLevel);
	
	currentFloor++;

	// Add enough room to world
	df::Vector v(view.getHorizontal(), view.getVertical());
	if (currentFloor > 1) {
		boundary.setHorizontal(boundary.getHorizontal() + 100);
	}

	if (boundary.getHorizontal() < v.getX()) {
		boundary.setHorizontal(v.getX());
	}
	if (boundary.getVertical() < v.getY()) {
		boundary.setVertical(v.getY());
	}
	WM.setBoundary(boundary);

	// TODO: load custom settings for next floor if implemented

	return 0;
}

int FloorManager::respawn() {
	// Create the player
	player = new Player();
	player->setPosition(currentCheckpoint->getPosition() - df::Vector(0, 2));
	player->setVelocity(df::Vector(0.5, 0));

	// Make camera follow player
	WM.setViewFollowing(player);
	WM.setViewSlack(df::Vector(0.25, 0.25));
	return 1;
}