/**
	A floor tile.
	@file Floor.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "Floor.h"

// Engine includes.
#include "dragonfly/DisplayManager.h"
#include "dragonfly/WorldManager.h"

Floor::Floor(df::Vector pos) {
	setType("Floor");
	setPosition(pos);
	WM.insertObject(this);
}

int Floor::draw() {
	return DM.drawCh(getPosition(), '-', df::Color::WHITE);
}
