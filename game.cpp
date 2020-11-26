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

// Tests.
#include "TestObject.h"

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
	RM.loadSprite("sprites/good-spr.txt", "good-spr"); // Test loading good sprite.
	RM.loadSprite("sprites/bad-spr.txt", "bad-spr"); // Test loading bad sprite.
	RM.loadSprite("sprites/nan-spr.txt", "nan-spr"); // Test loading non-existent sprite.
	
	RM.loadSprite("sprites/bad-spr.txt", "good-spr"); // Test loading good sprite again to check label overlap.

	// Test load all good sounds and music
	RM.loadSound("sounds/explode.wav", "explode");
	RM.loadSound("sounds/fire.wav", "fire");
	RM.loadSound("sounds/game-over.wav", "game-over");
	RM.loadSound("sounds/nuke.wav", "nuke");
	RM.loadMusic("sounds/start-music.wav", "start_music");

	// Test loading good sound and music again to check label overlap.
	RM.loadSound("sounds/explode.wav", "explode");
	RM.loadSound("sounds/start-music.wav", "start_music"); 

	// Test loading nonexistent sounds and music.
	RM.loadSound("sounds/abc.wav", "abc");
	RM.loadMusic("sounds/abc.wav", "abc");

	RM.getMusic("start_music")->play();
}

void unloadResources() {
	RM.unloadSprite("good-spr"); // Test unloading good sprite.
	RM.unloadSprite("bad-spr"); // Test unloading bad sprite that shouldn't be loaded.

	// Test unload all music and sounds
	RM.unloadSound("explode");
	RM.unloadSound("fire");
	RM.unloadSound("game-over");
	RM.unloadSound("nuke");

	RM.unloadMusic("start_music");
}

void populateGameWorld() {
	new df::TestObject(df::viewToWorld(df::Vector(0, 0)), df::Vector(0.4, 0)); // Draw and out test
	
	// Collision test
	new df::TestObject(df::viewToWorld(df::Vector(20, 20)), df::Vector(0, 0));
	new df::TestObject(df::viewToWorld(df::Vector(0, 20)), df::Vector(0.2, 0));
}