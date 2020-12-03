/**
	Keyboard event.
	@file EventKeyboard.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "EventKeyboard.h";

df::EventKeyboard::EventKeyboard() {
	setType(KEYBOARD_EVENT);
	m_key_val = df::Keyboard::Key::UNDEFINED_KEY;
	m_keyboard_action = df::EventKeyboardAction::UNDEFINED_KEYBOARD_ACTION;
}

void df::EventKeyboard::setKey(df::Keyboard::Key new_key) {
	m_key_val = new_key;
}

df::Keyboard::Key df::EventKeyboard::getKey() const {
	return m_key_val;
}

void df::EventKeyboard::setKeyboardAction(df::EventKeyboardAction new_action) {
	m_keyboard_action = new_action;
}

df::EventKeyboardAction df::EventKeyboard::getKeyboardAction() const {
	return m_keyboard_action;
}