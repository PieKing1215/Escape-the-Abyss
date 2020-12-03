/**
	Mouse event.
	@file EventMouse.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "EventMouse.h"

// Engine includes.
#include "DisplayManager.h"

df::EventMouse::EventMouse() {
	setType(MSE_EVENT);
	m_mouse_button = df::Mouse::Button::UNDEFINED_MOUSE_BUTTON;
	m_mouse_action = df::EventMouseAction::UNDEFINED_MOUSE_ACTION;
	df::Vector p(DM.getHorizontalPixels() / 2, DM.getVerticalPixels() / 2);
	m_mouse_xy = p;
}

void df::EventMouse::setMouseButton(Mouse::Button new_mouse_button) {
	m_mouse_button = new_mouse_button;
}

df::Mouse::Button df::EventMouse::getMouseButton() const {
	return m_mouse_button;
}

void df::EventMouse::setMouseAction(df::EventMouseAction new_mouse_action) {
	m_mouse_action = new_mouse_action;
}

df::EventMouseAction df::EventMouse::getMouseAction() const {
	return m_mouse_action;
}

void df::EventMouse::setMousePosition(df::Vector new_mouse_xy) {
	m_mouse_xy = new_mouse_xy;
}

df::Vector df::EventMouse::getMousePosition() const {
	return m_mouse_xy;
}