/**
	@file EventMouse.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __EVENT_MOUSE_H__
#define __EVENT_MOUSE_H__

#include "Event.h"
#include "Vector.h"

namespace df {

	const std::string MSE_EVENT = "df::mouse";

	// Set of mouse actions recognized by Dragonfly.
	enum class EventMouseAction {
		UNDEFINED_MOUSE_ACTION = -1,
		CLICKED,
		PRESSED,
		MOVED,
	};

	// Set of mouse buttons recognized by Dragonfly.
	namespace Mouse {
		enum class Button {
			UNDEFINED_MOUSE_BUTTON = -1,
			LEFT,
			RIGHT,
			MIDDLE,
		};
	} // end of namespace Mouse

	class EventMouse : public Event {

	private:
		EventMouseAction m_mouse_action; // Mouse action.
		Mouse::Button m_mouse_button; // Mouse button.
		Vector m_mouse_xy; // Mouse (x,y) coordinates.

	public:
		EventMouse();

		// Set mouse event's action.
		void setMouseAction(EventMouseAction new_mouse_action);

		// Get mouse event's action.
		EventMouseAction getMouseAction() const;

		// Set mouse event's button.
		void setMouseButton(Mouse::Button new_mouse_button);

		// Get mouse event's button.
		Mouse::Button getMouseButton() const;

		// Set mouse event's position.
		void setMousePosition(Vector new_mouse_xy);

		// Get mouse event's position.
		Vector getMousePosition() const;
	};

} // end of namespace df
#endif // __EVENT_MOUSE_H__
