/**
	@file Floor.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __FLOOR__
#define __FLOOR__

#include "dragonfly/Object.h"

class Floor : public df::Object {
public:
	Floor(df::Vector pos);
	int draw();
};

#endif // __FLOOR__
