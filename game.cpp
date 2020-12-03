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
#include "WorldManager.h"
#include "utility.h"

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
	RM.loadSprite("sprites/player-attack-spr.txt", "player-attack");
	RM.loadSprite("sprites/player-walk-spr.txt", "player-walk");
	RM.loadSprite("sprites/player-idle-body-spr.txt", "player-idle-body");
	RM.loadSprite("sprites/player-idle-feet-spr.txt", "player-idle-feet");
	RM.loadSprite("sprites/player-bounds.txt", "player-bounds");
	RM.loadSprite("sprites/wall1.txt", "wall1");
}

void unloadResources() {
	RM.unloadSprite("bat");
	RM.unloadSprite("slime");
	RM.unloadSprite("player-attack");
	RM.unloadSprite("player-walk");
	RM.unloadSprite("player-idle-body");
	RM.unloadSprite("player-idle-feet");
	RM.unloadSprite("player-bounds");
	RM.unloadSprite("wall1");
}

void populateGameWorld() {
	
	// make a floor for testing
	for(int x = 0; x < 100; x++) {
		for(int y = 0; y < 3; y++) {
			Wall* w = new Wall();
			int height = (int)(sin(x / 10.0f) * 2.0f + sin(x / 3.14f) * 2.0f);
			w->setPosition({10.0f + x, 20.0f + y + height});
		}
	}

	Wall* wa = new Wall();
	wa->setPosition({27, 15});

	// spawn some enemies
	EnemyBat* bat = new EnemyBat();
	bat->setPosition({30, 8});
	EnemyBat* bat2 = new EnemyBat();
	bat2->setPosition({50, 8});
	EnemySlime* slime = new EnemySlime();
	slime->setPosition({40, 15});
	slime->setVelocity({0, 0.1});

	// spawn the player
	Player* pl = new Player();
	pl->setPosition({15, 14});
	pl->setVelocity({0.5f, -0.1f});

	// set world boundary to be 2 screens wide
	int screensX = 2;
	int screensY = 1;
	df::Vector v = df::pixelsToSpaces(df::Vector(DM.getHorizontalPixels(), DM.getVerticalPixels())), w(DM.getHorizontal() * screensX, DM.getVertical() * screensY);
	if(w.getX() < v.getX()) {
		w.setX(v.getX());
	}
	if(w.getY() < v.getY()) {
		w.setY(v.getY());
	}
	df::Box boundary = df::Box(df::Vector() - ((w - v) / 2.0), w.getX(), w.getY());
	WM.setBoundary(boundary);

	// make camera follow player
	WM.setViewFollowing(pl);
}