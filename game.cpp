/**
	Main game driver.
	@file game.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

// Engine includes.
#include "dragonfly/DisplayManager.h"
#include "dragonfly/LogManager.h"
#include "dragonfly/GameManager.h"
#include "dragonfly/ResourceManager.h"
#include "dragonfly/WorldManager.h"
#include "dragonfly/utility.h"

#include "Wall.h"
#include "Player.h"
#include "EnemyBat.h"
#include "EnemySlime.h"

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
	RM.loadSprite("sprites/slime-spr.txt", "slime");
	RM.loadSprite("sprites/player-attack-spr-r.txt", "player-attack-r");
	RM.loadSprite("sprites/player-attack-spr-l.txt", "player-attack-l");
	RM.loadSprite("sprites/player-walk-spr.txt", "player-walk");
	RM.loadSprite("sprites/player-idle-body-spr.txt", "player-idle-body");
	RM.loadSprite("sprites/player-idle-feet-spr.txt", "player-idle-feet");
	RM.loadSprite("sprites/player-bounds.txt", "player-bounds");
	RM.loadSprite("sprites/wall1.txt", "wall1");
}

void unloadResources() {
	RM.unloadSprite("bat");
	RM.unloadSprite("slime");
	RM.unloadSprite("player-attack-l");
	RM.unloadSprite("player-attack-r");
	RM.unloadSprite("player-walk");
	RM.unloadSprite("player-idle-body");
	RM.unloadSprite("player-idle-feet");
	RM.unloadSprite("player-bounds");
	RM.unloadSprite("wall1");
}

void populateGameWorld() {
	// set world boundary to be 2 screens wide
	int screensX = 2;
	int screensY = 1;
	df::Vector v = df::pixelsToSpaces(df::Vector(DM.getHorizontalPixels(), DM.getVerticalPixels())), w(DM.getHorizontal() * screensX, DM.getVertical() * screensY);
	if (w.getX() < v.getX()) {
		w.setX(v.getX());
	}
	if (w.getY() < v.getY()) {
		w.setY(v.getY());
	}
	df::Box boundary = df::Box(df::Vector() - ((w - v) / 2.0), w.getX(), w.getY());
	WM.setBoundary(boundary);
}