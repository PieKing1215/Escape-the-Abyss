/**
	A floor tile.
	@file Floor.cpp
	@author
*/

#include "Floor.h"

// Engine includes.
#include "DisplayManager.h"
#include "WorldManager.h"

Floor::Floor(df::Vector pos) {
	setType("Floor");
	setPosition(pos);
	WM.insertObject(this);
}

int Floor::draw() {
	return DM.drawCh(getPosition(), '-', df::Color::WHITE);
}
