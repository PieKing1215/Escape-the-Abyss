/**
	@file Checkpoint.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __CHECKPOINT_H__
#define __CHECKPOINT_H__

// Engine includes
#include "dragonfly/Object.h"

class Checkpoint : public df::Object {
	public:
		Checkpoint(df::Vector pos, int width, int height);
		virtual int eventHandler(const df::Event* p_e);
	};
#endif // __CHECKPOINT_H__
