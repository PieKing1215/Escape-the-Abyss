/**
	A wall tile.
	@file Wall.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "Wall.h"

// Engine includes.
#include "dragonfly/DisplayManager.h"
#include "dragonfly/WorldManager.h"

Wall::Wall(df::Vector pos) : Object() {
	setType("Wall");
	setPosition(pos);
	WM.insertObject(this);
}

int Wall::draw() {
	return DM.drawCh(getPosition(), '|', df::Color::WHITE);
}
