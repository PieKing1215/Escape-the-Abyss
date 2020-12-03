/**
	Floor manager.
	@file FloorManager.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "FloorManager.h"

// Engine inludes.
#include "dragonfly/LogManager.h"
#include "dragonfly/WorldManager.h"

// Game includes.
#include "Floor.h"
#include "Player.h"

FloorManager::FloorManager() {
	setType("FloorManager");
	// TODO: set this based on save file read.
	currentFloor = 0;
	floorSize = 5;
	maxFloorHeight = 20;
	minFloorHeight = -20;
	noise = 30;
}

FloorManager::FloorManager(FloorManager const&) {
	setType("FloorManager");
	// TODO: set this based on save file read.
	currentFloor = 0;
	floorSize = 5;
	maxFloorHeight = 20;
	minFloorHeight = -20;
	noise = 30;
}

void FloorManager::operator=(FloorManager const&) {

}

FloorManager& FloorManager::getInstance() {
	static FloorManager floorManager;
	return floorManager;
}

int FloorManager::startUp() {
	if (FloorManager::nextFloor()) {
		writeLog("ERROR", "Error creating foor.");
		return -1;
	}
	return df::Manager::startUp();
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
	df::ObjectList ol = WM.getAllObjects();
	df::ObjectListIterator li(&ol);
	li.first();
	while (!li.isDone()) {
		if (li.currentObject()->getType() == "Player") {
			// TODO: save any stats stored on player
		}
		WM.removeObject(li.currentObject());
		delete li.currentObject();
	}

	// Create floor
	srand(currentFloor + 1);
	int height = rand() % (maxFloorHeight - minFloorHeight) + minFloorHeight, floorHeight = 0;
	for (int x = 0; x < 100; x++) {
		if (x % floorSize == 0) {
			height -= rand() % (maxFloorHeight - minFloorHeight) + minFloorHeight;
			if (abs(height) >= (maxFloorHeight - minFloorHeight) - noise) {
				if (height > 0 && floorHeight < maxFloorHeight) {
					floorHeight++;
				}
				else if (floorHeight > minFloorHeight) {
					floorHeight--;
				}
			}
		}
		// simple sin wave for testing. height = (int)(sin(x / 10.0f) * 2.0f + sin(x / 3.14f) * 2.0f);
		new Floor(df::Vector(10.0f + x, 20.0f + floorHeight));
	}

	// Spawn the player
	Player* pl = new Player();
	pl->setPosition({ 15, 14 });
	pl->setVelocity({ 0.5f, -0.1f });

	// TODO: write any saved stats to player

	// Spawn enemies

	// Make camera follow player
	WM.setViewFollowing(pl);

	currentFloor++;

	// TODO: load custom settings for next floor if implemented

	return 0;
}