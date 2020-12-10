/**
	@file Wall.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#include "dragonfly/Object.h"

#ifndef __WALL__
#define __WALL__

class Wall : public df::Object {
public:
	Wall(df::Vector pos);
	int draw();
};

#endif // __WALL__
