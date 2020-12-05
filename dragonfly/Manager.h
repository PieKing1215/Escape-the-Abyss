/**
	@file Manager.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __MANAGER_H__
#define __MANAGER_H__

// System includes.
#include <string>

// Engine includes.
#include "Event.h"
#include "ObjectList.h"

namespace df {
	const int MAX_EVENTS = 100;
	class Manager {
	private:
		std::string m_type = ""; // Manager type identifier.
		bool m_is_started; // True if startUp() succeeded.
		std::string* event; // List of events.
		ObjectList* obj_list; // Objects interested in event.
		int event_count; // Number of events.

		// Check if event is handled by this Manager.
		// If handled, return true else false.
		// (Base Manager always returns false.)
		virtual bool isValid(std::string event_name) const;
	protected:
		// Set type identifier of Manager.
		void setType(std::string new_type);
		// Writes to log with the manager type being the reporter
		int writeLog(std::string warn, const char* fmt, ...) const;
	public:
		// Default constructor.
		Manager();
		// Default destructor.
		virtual ~Manager();
		// Get type identifier of Manager.
		std::string getType() const;
		// Startup Manager. 
		// Return 0 if ok, else negative number.
		virtual int startUp();
		// Shutdown Manager.  
		virtual void shutDown();
		// Return status of is_started (true when startUp() was successful).
		bool isStarted() const;
		// Indicate interest in event.
		// Return 0 if ok, else −1.
		// (Note, doesn’t check to see if Object is already registered.)
		int registerInterest(Object* p_o, std::string event_type);
		// Indicate no more interest in event.
		// Return 0 if ok, else −1.
		int unregisterInterest(Object* p_o, std::string event_type);
		// Send event to all interested Objects.
		// Return count of number of events sent.
		int onEvent(const Event* p_event) const;
	};
} // end of namespace df
#endif // __MANAGER_H__