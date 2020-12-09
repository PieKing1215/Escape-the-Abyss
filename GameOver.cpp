/**
	Game Over screen that returns player to GameStart.
	@file GameOver.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

// Engine includes.
#include "dragonfly/EventStep.h"
#include "dragonfly/GameManager.h"
#include "dragonfly/WorldManager.h"
#include "dragonfly/ResourceManager.h"
#include "dragonfly/utility.h"

// Game includes.
#include "GameOver.h"

GameOver::GameOver() {
	setType("GameOver");
	df::Box v = WM.getView();
	setPosition(df::viewToWorld(df::Vector(v.getHorizontal(), v.getVertical()) / 2)); // Set location to center
	registerInterest(df::STEP_EVENT);
	if (setSprite("gameover") == 0) {
		time_to_live = getAnimation()->getSprite()->getFrameCount() * getAnimation()->getSprite()->getSlowdown() + 90;
	} else {
		time_to_live = 0;
	}
}

GameOver::~GameOver() {
	GM.setGameOver();
}

int GameOver::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) { // On step
		step();
		return 1;
	}
	return 0;
}

// Decrement time_to_live, then kill when below 0
void GameOver::step() {
	time_to_live--;
	if (time_to_live <= 0) {
		WM.markForDelete(this);
	}
}

int GameOver::draw() {
	return df::Object::draw();
}