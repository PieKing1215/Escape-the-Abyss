/**
	Event step that fires every frame.
	@file EventStep.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "EventStep.h"

df::EventStep::EventStep() {
	setType(df::STEP_EVENT);
	m_step_count = 0;
}

df::EventStep::EventStep(int init_step_count) {
	setType(df::STEP_EVENT);
	m_step_count = init_step_count;
}

void df::EventStep::setStepCount(int new_step_count) {
	m_step_count = new_step_count;
}

int df::EventStep::getStepCount() const {
	return m_step_count;
}