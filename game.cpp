/**
	Main game driver.
	@file game.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

// Engine includes.
#include "DisplayManager.h"
#include "LogManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "utility.h"

// Function prototypes.
void loadResources();
void unloadResources();
void populateGameWorld();

int main(int argc, char* argv[]) {
	// Start up game manager.
	if (GM.startUp()) {
		LM.writeLog("ERROR", "Driver", "Error starting GameManager.");
		GM.shutDown();
		return 0;
	}

	// Start up resource manager.
	if (RM.startUp()) {
		LM.writeLog("ERROR", "Driver", "Error starting ResourceManager.");
		RM.shutDown();
		return 0;
	}

	// Set flush of logfile during development. True if not production. False otherwise.
	LM.setFlush(true);

	// Load game resources.
	loadResources();

	// Populate the game world
	populateGameWorld();

	// Run game.
	GM.run();

	// Unload game resources.
	unloadResources();

	// Shut everything down.
	GM.shutDown();
}

void loadResources() {
	RM.loadSprite("sprites/bat-spr.txt", "bat");
	RM.loadSprite("sprites/player-attack-spr.txt", "player-attack");
	RM.loadSprite("sprites/player-walk-spr.txt", "player-walk");
	RM.loadSprite("sprites/player-idle-body-spr.txt", "player-idle-body");
	RM.loadSprite("sprites/player-idle-ffet-spr.txt", "player-idle-feet");
}

void unloadResources() {
	RM.unloadSprite("bat");
	RM.unloadSprite("player-attack");
	RM.unloadSprite("player-walk");
	RM.unloadSprite("player-idle-body");
	RM.unloadSprite("player-idle-feet");
}

void populateGameWorld() {
	
}