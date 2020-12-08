/**
	A checkpoint box.
	@file Checkpoint.cpp
	@author
*/

#include "Checkpoint.h"

// Engine includes.
#include "dragonfly/DisplayManager.h"
#include "dragonfly/WorldManager.h"
#include "dragonfly/EventCollision.h"

// Game includes.
#include "FloorManager.h"
#include "GameOver.h"

Checkpoint::Checkpoint(df::Vector pos, int width, int height, bool finalCheckpoint) {
	setType("Checkpoint");
	setSolidness(df::Solidness::SOFT); // Only overlaps objects
	setPosition(pos);
	setBox(df::Box(df::Vector(-1.0 * width / 2.0, -1.0 * height / 2.0), width, height));
	fired = false;
	isFinal = finalCheckpoint;
	WM.insertObject(this);

	registerInterest(df::COLLISION_EVENT);
}

bool Checkpoint::hasFired() const {
	return fired;
}

int Checkpoint::eventHandler(const df::Event* p_e) {
	if (!fired && p_e->getType() == df::COLLISION_EVENT) {
		if (((df::EventCollision*)p_e)->getObject1()->getType() == "Player") {
			fired = true;
			if (isFinal) {
				((Player*)((df::EventCollision*)p_e)->getObject1())->endAnim();
				new GameOver;
			}
			else {
				FM.nextFloor();
			}
			return 1;
		}
	}
	return 0;
}

/*
int Checkpoint::draw() {
	std::string tmp = "";
	for (int i = 0; i < getBox().getHorizontal(); i++) {
		tmp += "*";
	}
	return DM.drawString(getPosition(), tmp, df::Justification::LEFT_JUSTIFIED, df::Color::YELLOW);
}
*/

