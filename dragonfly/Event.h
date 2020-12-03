/**
	@file Event.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __EVENT_H__
#define __EVENT_H__

// System includes.
#include <string>

namespace df {
	const std::string UNDEFINED_EVENT = "df::undefined";
	class Event {
	private:
		std::string m_event_type; // Event type.
	public:
		// Create base event.
		Event();
		// Destructor.
		virtual ~Event();
		// Set event type.
		void setType(std::string new_type);  
		// Get event type.
		std::string getType() const;
	}; 
} // end of namespace df
#endif // __EVENT_H__
