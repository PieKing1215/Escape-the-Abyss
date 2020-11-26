/**
	Out of bounds event.
	@file EventOut.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "EventOut.h"

df::EventOut::EventOut() {
	setType(OUT_EVENT);
	hard = false;
}

df::EventOut::EventOut(bool is_hard) {
	setType(OUT_EVENT);
	hard = is_hard;
}

bool df::EventOut::isHard() const {
	return hard;
}