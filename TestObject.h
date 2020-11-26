/**
	@file TestObject.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __TESTOBJECT_H__
#define __TESTOBJECT_H__

// Engine includes.
#include "Object.h"

namespace df {
	const std::string TEST_DRAW_STRING = "123 Test";
	class TestObject : public Object {
	private:
		int kill; // Int used to track number of frames it's alive so it can die.
	public:
		TestObject();
		TestObject(Vector start_pos, Vector velocity);
		int eventHandler(const Event* p_event);
	};
} // end of namespace df
#endif // __TESTOBJECT_H__