/**
	Manager master.
	@file Manager.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "Manager.h"

// Engine includes
#include "LogManager.h"
#include "WorldManager.h"
#include "ObjectListIterator.h"
#include "utility.h"

// System includes.
#include <stdarg.h>

df::Manager::Manager() {
	m_type = "Manager";
	m_is_started = false;
	event_count = 0;
	event = new std::string[MAX_EVENTS];
	obj_list = new df::ObjectList[MAX_EVENTS];
}

df::Manager::~Manager() {

}

void df::Manager::setType(std::string new_type) {
	m_type = new_type;
}

std::string df::Manager::getType() const {
	return m_type;
}

int df::Manager::startUp() {
	m_is_started = true;
	writeLog("", "Started.");
	return 0;
}

void df::Manager::shutDown() {
	m_is_started = false;
	if (LM.isStarted()) {
		writeLog("", "Stopped.");
	}
}

bool df::Manager::isStarted() const {
	return m_is_started;
}

bool df::Manager::isValid(std::string event_name) const {
	for (int i = 0; i < event_count; i++) {
		if (event[i] == event_name) {
			return true;
		}
	}
	return false;
}

int df::Manager::registerInterest(df::Object* p_o, std::string event_type) {
	for (int i = 0; i < event_count; i++) {
		if (event[i] == event_type) {
			obj_list[i].insert(p_o);
			return 0;
		}
	}
	if (event_count >= MAX_EVENTS) {
		return -1;
	}
	event[event_count] = event_type;
	obj_list[event_count].clear();
	obj_list[event_count].insert(p_o);
	event_count++;
	LM.writeLog("ALERT", p_o->getType() + " " + df::toString(p_o->getId()), "Can now recieve events of type '%s'.", event_type.c_str());
	return 0;
}

int df::Manager::unregisterInterest(df::Object* p_o, std::string event_type) {
	for (int i = 0; i < event_count; i++) {
		if (event[i] == event_type) {
			obj_list[i].remove(p_o);
			writeLog("ALERT", "Can now not recieve events of type '%s'", event_type.c_str());
			if (obj_list[i].isEmpty()) {
				for (int j = i; j < event_count - 1; j++) {
					event[j] = event[j + 1];
					obj_list[j] = obj_list[j + 1];
				}
				event_count--;
			}
			break;
		}
	}
	return 0;
}

int df::Manager::onEvent(const df::Event* p_event) const {
	int count = 0;
	for (int i = 0; i < event_count; i++) {
		if (event[i] == p_event->getType()) {
			df::ObjectListIterator li(&obj_list[i]);
			li.first();
			while (!li.isDone() && li.currentObject()) {
				li.currentObject()->eventHandler(p_event);
				count++;
				li.next();
			}
		}
	}
	return count;
}

int df::Manager::writeLog(std::string warn, const char* fmt, ...) const {
	va_list args;
	va_start(args, fmt);
	int x = LM.writeLog(warn, getType(), fmt, args);
	va_end(args);
	return x;
}