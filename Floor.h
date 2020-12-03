/**
	@file Floor.h
	@author
*/
#pragma once

#ifndef __FLOOR__
#define __FLOOR__

#include "Object.h"

class Floor : public df::Object {
public:
	Floor(df::Vector pos);
	int draw();
};

#endif // __FLOOR__
