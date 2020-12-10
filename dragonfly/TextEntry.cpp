/**
	A view object for entering text.
	@file TextEntry.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "TextEntry.h"

// Engine includes.
#include "EventKeyboard.h"
#include "EventStep.h"
#include "utility.h"

df::TextEntry::TextEntry() {
	m_text = "";
	m_limit = 0;
	m_numbers_only = false;
	m_cursor = 0;
	m_cursor_char = 0;
	m_blink_rate = 0;
	registerInterest(df::STEP_EVENT);
	registerInterest(df::KEYBOARD_EVENT);
}

int df::TextEntry::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		static int blink = -1 * getBlinkRate();
		if (blink >= 0) {
			m_text.replace(m_cursor, 1, 1, getCursorChar());
		}
		else {
			m_text.replace(m_cursor, 1, 1, ' ');
		}
		return 1;
	}
	const df::EventKeyboard* p_ke = dynamic_cast<const df::EventKeyboard*>(p_e);
	if (p_e->getType() == df::KEYBOARD_EVENT && p_ke->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED) {
		if (p_ke->getKey() == df::Keyboard::Key::RETURN) {
			callback();
			return 1;
		}
		if (p_ke->getKey() == df::Keyboard::Key::BACKSPACE) {
			if (m_cursor > 0) {
				if (m_cursor < m_limit) {
					m_text.replace(m_cursor, 1, 1, ' ');
				}
				m_cursor--;
				m_text.replace(m_cursor, 1, 1, ' ');
			}
			return 1;
		}
		if (m_cursor >= m_limit) {
			return 1;
		}
		std::string str = df::toString(static_cast<int>(p_ke->getKey()));
		if (numbersOnly() && !isdigit(str[0])) {
			return 1;
		}
		m_text.replace(m_cursor, 1, str);
		m_cursor++;
		return 1;
	}
	return df::ViewObject::eventHandler(p_e);
}

void df::TextEntry::setText(std::string new_text) {
	m_text = new_text;
}

std::string df::TextEntry::getText() const {
	return m_text;
}

void df::TextEntry::setLimit(int new_limit) {
	m_limit = new_limit;
}

int df::TextEntry::getLimit() const {
	return m_limit;
}

void df::TextEntry::setCursor(int new_cursor) {
	m_cursor = new_cursor;
}

int df::TextEntry::getCursor() const {
	return m_cursor;
}

void df::TextEntry::setBlinkRate(int new_blink_rate) {
	m_blink_rate = new_blink_rate;
}

int df::TextEntry::getBlinkRate() const {
	return m_blink_rate;
}

bool df::TextEntry::numbersOnly() const {
	return m_numbers_only;
}

void df::TextEntry::setNumbersOnly(bool new_numbers_only) {
	m_numbers_only = new_numbers_only;
}

void df::TextEntry::setCursorChar(char new_cursor_char) {
	m_cursor_char = new_cursor_char;
}

char df::TextEntry::getCursorChar() const {
	return m_cursor_char;
}

int df::TextEntry::draw() {
	std::string view_str = getViewString();
	setViewString(view_str + m_text);
	ViewObject::draw();
	setViewString(view_str);
	return 0;
}