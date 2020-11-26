/**
	@file EventOut.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __EVENT_OUT_H__
#define __EVENT_OUT_H__

#include "Event.h"

namespace df {

	const std::string OUT_EVENT = "df::out";

	class EventOut : public Event {
	private:
		bool hard; // Signifies if out event for view or boundary.
	public:
		EventOut();
		EventOut(bool hard);
		bool isHard() const;
	};

} // end of namespace df
#endif // __EVENT_OUT_H__
