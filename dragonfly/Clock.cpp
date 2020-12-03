/**
	Delta timer.
	@file Clock.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "Clock.h"

// Engine includes.
#include "LogManager.h"
#include "utility.h"

df::Clock::Clock() {
	LM.writeLog("", "Clock", "Delta clock started. Reported start time: %s UTC", df::getTimeString().c_str());
	delta();
}

long int df::Clock::delta() {
	long int time_s = df::getTime(); // Convert current system time to microseconds
	long int d = time_s - m_previous_time; // Delta time
	m_previous_time = time_s; // Reset timer
	if (d < 0) {
		return -1;
	}
	return d;
}

long int df::Clock::split() const {
	long int d = df::getTime() - m_previous_time; // Convert current system time to microseconds and get delta time
	if (d < 0) {
		return -1;
	}
	return d;
}