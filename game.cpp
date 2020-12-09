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

	// Run game.
	GM.run();

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
	RM.loadSprite("sprites/gameover-spr.txt", "gameover");
	RM.loadSprite("sprites/startmenu-spr.txt", "startmenu");
}