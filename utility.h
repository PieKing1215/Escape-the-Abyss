/**
	@file utility.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __UTILITY_H__
#define __UTILITY_H__

// Engine includes
#include "Box.h"
#include "EventKeyboard.h"
#include "Object.h"
#include "Vector.h"

namespace df {
	// Return true if the two vectors are within 1 unit of each other (inclusive).
	bool positionsIntersect(Vector p1, Vector p2);

	// Return true if value is between min and max (inclusive).
	bool valueInRange(float value, float min, float max);

	// Return true if Boxes intersect.
	bool boxIntersectsBox(Box box1, Box box2);

	// Return true if pos intersects box.
	bool boxContainsPosition(Box box, Vector pos);

	// Convert relative bounding Box for Object to absolute world Box.
	Box getWorldBox(const Object* p_o);

	// Convert relative bounding Box for Object to absolute world Box
	// at postion where.
	Box getWorldBox(const Object* p_o, Vector where);

	// Convert world position to view position.
	Vector worldToView(Vector world_pos);

	// Convert view position to world position.
	Vector viewToWorld(Vector view_pos);

	// Convert to string.
	std::string toString(int i);
	std::string toString(float i);
	std::string toString(long i);
	std::string toString(unsigned long i);
	std::string toString(Vector i);
	std::string toString(Box i);

	// Return the current time of day in milliseconds.
	long int getTime();

	// Return the current time as a formatted time string: HH:MM:SS.MMMM
	std::string getTimeString();

	// Generate random integer
	int rand();

	// Generate random integer with seed specified. Subsequent calls of rand() are based on this seed and it's generated numbers.
	int rand(unsigned long seed);
} // end of namespace df
#endif // __UTILITY_H__
