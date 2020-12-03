/**
	Event master.
	@file Event.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "Event.h"

df::Event::Event() {
	m_event_type = "";
}

df::Event::~Event() {

}

void df::Event::setType(std::string new_type) {
	m_event_type = new_type;
}

std::string df::Event::getType() const {
	return m_event_type;
}