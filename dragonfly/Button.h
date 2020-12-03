/**
	@file Button.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __BUTTON_H__
#define __BUTTON_H__

// Engine includes.
#include "ViewObject.h"
#include "EventMouse.h"

namespace df {
	class Button : public ViewObject {
	private:
		Color m_highlight_color; // Color when highlighted.
		Color m_default_color; // Color when not highlighted.
	public:
		Button();

		// Handle "mouse" events.
		// Return 0 if ignored, else 1.
		int eventHandler(const Event* p_e);

		// Set highlight (when mouse over) color for Button
		void setHighlightColor(Color new_highlight_color);

		//  Get highlist (when mouse over) color for Button
		Color getHighlightColor() const;

		// Set default (when mouse not over) color for Button
		void setDefaultColor(Color new_default_color);

		//  Get default (when mouse not over) color for Button
		Color setDefaultColor() const;

		// Return true if mouse over Button, else false.
		bool mouseOverButton(const EventMouse* p_e) const;

		// Called when Button clicked.
		// Must be defined by derived clas.
		virtual void callback() = 0;
	};
} // end of namespace df
#endif // __BUTTON_H__
