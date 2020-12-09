/**
	@file WorldManager.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __FLOOR_MANAGER_H__
#define __FLOOR_MANAGER_H__

// Engine includes.
#include "dragonfly/Manager.h"

// Game includes.
#include "Player.h"
#include "Checkpoint.h"

#define FM FloorManager::getInstance()

class FloorManager : public df::Manager {
private:
	FloorManager();                 // Private since a singleton.
	FloorManager(FloorManager const&);  // Don't allow copy.
	void operator=(FloorManager const&); // Don't allow assignment.
	int currentFloor; // The current floor. Start from 1.
	int floorSize; // The width of the floor in characters.
	int noise; // A higher number causes more topographical terrain. 0<=noise<=100
	int previousEndHeight; // The previous ending height.
	Player* player; // The player pointer.
	int worldHeight;
	int maxLevel;
	Checkpoint* nextCheckpoint;
	Checkpoint* currentCheckpoint;
	long seed;
public:
	// Get the one and only instance of the FloorManager.
	static FloorManager& getInstance();

	// Startup.
	// Return 0.
	int startUp();

	// Shutdown.
	void shutDown();

	// Get current floor.
	int getFloor() const;

	// Set current floor.
	void setFloor(int new_floor);

	// Set current floor.
	void setFloorSize(int new_floor_size);

	// Set noise.
	void setNoise(int new_noise);

	// Clear this floor and load the next floor.
	// Return 0 on success, -1 otherwise
	int nextFloor();

	int respawn();
};
#endif // __FLOOR_MANAGER_H__