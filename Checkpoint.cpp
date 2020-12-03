/**
	A checkpoint box.
	@file Checkpoint.cpp
	@author
*/

#include "Checkpoint.h"

// Engine includes.
#include "dragonfly/WorldManager.h"
#include "dragonfly/EventCollision.h"

// Game includes.
#include "EventCheckpoint.h"

Checkpoint::Checkpoint(df::Vector pos, int width, int height) {
	setType("Checkpoint");
	setSolidness(df::Solidness::SOFT); // Only overlaps objects
	setPosition(pos);
	// Make a sprite with the correct width and height specks for overlap box
	df::Sprite* sprite = new df::Sprite(0);
	sprite->setWidth(width);
	sprite->setHeight(height);
	getAnimation()->setSprite(sprite);
	WM.insertObject(this);

	registerInterest(df::COLLISION_EVENT);
}

int Checkpoint::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		EventCheckpoint ec;
		WM.onEvent(&ec);
		return 1;
	}
	return 0;
}