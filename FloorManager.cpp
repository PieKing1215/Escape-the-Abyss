/**
	Floor manager.
	@file FloorManager.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "FloorManager.h"

// Engine inludes.
#include "dragonfly/DisplayManager.h"
#include "dragonfly/LogManager.h"
#include "dragonfly/WorldManager.h"

// Game includes.
#include "Checkpoint.h"
#include "Floor.h"
#include "Player.h"

#include "EnemySlime.h"
#include "EnemyBat.h"

FloorManager::FloorManager() {
	setType("FloorManager");
	// TODO: set this based on save file read.
	currentFloor = 0;
	floorSize = 5;
	maxFloorHeight = 20;
	minFloorHeight = -20;
	noise = 30;
	previousEndHeight = 0;
	player = NULL;
}

FloorManager::FloorManager(FloorManager const&) {
	setType("FloorManager");
	// TODO: set this based on save file read.
	currentFloor = 0;
	floorSize = 5;
	maxFloorHeight = 20;
	minFloorHeight = -20;
	noise = 30;
	player = NULL;
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

void FloorManager::setMaxFloorHeight(int new_height) {
	maxFloorHeight = new_height;
}

void FloorManager::setMinFloorHeight(int new_height) {
	minFloorHeight = new_height;
}

void FloorManager::setNoise(int new_noise) {
	noise = new_noise;
}

int FloorManager::nextFloor() {
	// Clear all objects
	/*df::ObjectList ol = WM.getAllObjects();
	df::ObjectListIterator li(&ol);
	li.first();
	while (!li.isDone()) {
		if (li.currentObject()->getType() != "Player") {
			WM.markForDelete(li.currentObject());
		}
		li.next();
	}*/

	// Create floor
	srand(currentFloor + 1);
	int floorHeight = previousEndHeight, levelWidth = 100, enemyMultiplier = (((levelWidth - 15) / 100) - 5) * currentFloor, enemies = 0;
	if (enemyMultiplier <= 0) {
		enemyMultiplier = 1;
	}
	const float groundToAir = (float)(rand() % 10) / 10.0;
	const int totalEnemies = rand() % enemyMultiplier + 5;

	for (int x = 0; x < levelWidth; x++) {
		srand((currentFloor + 1) * (x + 2) * (rand() % 50));
		if (x % floorSize == 0) {
			int height = rand() % (maxFloorHeight - minFloorHeight) + minFloorHeight;
			if (abs(height) >= (maxFloorHeight - minFloorHeight) - noise) {
				if (height >= 0 && floorHeight < maxFloorHeight) {
					floorHeight++;
				}
				else if (floorHeight > minFloorHeight) {
					floorHeight--;
				}
			}
		}
		// simple sin wave for testing. height = (int)(sin(x / 10.0f) * 2.0f + sin(x / 3.14f) * 2.0f);
		new Floor(df::Vector((currentFloor * levelWidth) + 10.0f + x, 20.0f + floorHeight));

		// Check if this floor tile should have an enemy spawned above it.
		if (enemies < totalEnemies && (currentFloor > 0 && x % (levelWidth / totalEnemies) == 0) || (currentFloor == 0 && x > 25 && x % (levelWidth / totalEnemies) == 0)) {
			float tmp = (float)(rand() % 10) / 10.0;
			// TOOD: there is a big performance hit on enemy spawning but not floor spawning
			if (tmp < groundToAir) {
				EnemySlime* slime = new EnemySlime();
				slime->setPosition(df::Vector((currentFloor * levelWidth) + 10.0f + x, 20.0f + floorHeight - 4));
			}
			else {
				EnemyBat* bat = new EnemyBat();
				bat->setPosition(df::Vector((currentFloor * levelWidth) + 10.0f + x, 20.0f + floorHeight - 6));
			}
			enemies++;
		} else if (!player && x == 0) {
			// Create the player
			player = new Player();
			player->setPosition({ 5, 0 });
			player->setVelocity({ 0.5f, -0.1f });
			
			// Make camera follow player
			WM.setViewFollowing(player);
		}
	}

	previousEndHeight = floorHeight;

	// Create checkpoint the end of the level
	new Checkpoint(df::Vector((currentFloor * levelWidth) + (levelWidth / 2), DM.getVertical() / 2), 1, DM.getVertical());

	currentFloor++;

	// Add enough room to world
	df::Vector v(WM.getView().getHorizontal(), WM.getView().getVertical()), w;
	if (currentFloor > 1) {
		w.setXY(WM.getBoundary().getHorizontal() + 100, DM.getVertical());
	}
	else {
		w.setXY(DM.getHorizontal() * 2, DM.getVertical());
	}

	if (w.getX() < v.getX()) {
		w.setX(v.getX());
	}
	if (w.getY() < v.getY()) {
		w.setY(v.getY());
	}
	df::Box boundary = df::Box(df::Vector() - ((w - v) / 2.0), w.getX(), w.getY());
	WM.setBoundary(boundary);
	              
	// TODO: load custom settings for next floor if implemented

	return 0;
}