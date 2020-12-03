/**
	@file EventCheckpoint.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __EVENT_CHECKPOINT_H__
#define __EVENT_CHECKPOINT_H__

#include "dragonfly/Event.h"
const std::string CHECKPOINT_EVENT = "checkpoint";
class EventCheckpoint : public df::Event {
public:
	EventCheckpoint();
};
#endif // __EVENT_CHECKPOINT_H__