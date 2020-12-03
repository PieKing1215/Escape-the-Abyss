/**
	@file TextEntry.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __TEXTENTRY_H__
#define __TEXTENTRY_H__

// Engine includes.
#include "EventMouse.h"
#include "ViewObject.h"

namespace df {
	class TextEntry : public ViewObject {
	private:
		std::string m_text; // Text entered.
		int m_limit; // Character limit in text.
		bool m_numbers_only; // True if only numbers.
		int m_cursor; // Cursor location.
		char m_cursor_char; // Cursor character.
		int m_blink_rate; // Cursor blink rate.
	public:
		TextEntry();

		// Set text entered.
		void setText(std::string new_text);

		// Get text entered.
		std::string getText() const;

		// Handle "keyboard" events.
		// Return 0 if ignored, else 1.
		int eventHandler(const Event* p_e);

		// Called when TextEntry enter hit.
		// Must be defined by derived class.
		virtual void callback() = 0;

		// Set limit of number of characters allowed.
		void setLimit(int new_limit);

		// Get limit of number of character allowed.
		int getLimit() const;

		// Set cursor to location.
		void setCursor(int new_cursor);

		// Get cursor location.
		int getCursor() const;

		// Set blink rate for cursor (in ticks)
		void setBlinkRate(int new_blink_rate);

		// Get blink rate for cursor (in ticks)
		int getBlinkRate() const;

		// Return true if only number can be entered.
		bool numbersOnly() const;

		// Set to allow only numbers to be entered.
		void setNumbersOnly(bool new_numbers_only = true);

		// Set cursor character.
		void setCursorChar(char new_cursor_char);

		// Get cursor character.
		char getCursorChar() const;

		// Draw viewstring + text entered
		virtual int draw();
	};
}// end of namespace df
#endif // __TEXTENTRY_H__