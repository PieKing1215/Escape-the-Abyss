#include "Button.h"

// Engine includes.
#include "utility.h"

df::Button::Button() {
	m_highlight_color = df::COLOR_DEFAULT;
	m_default_color = df::COLOR_DEFAULT;
}

int df::Button::eventHandler(const df::Event* p_e) {
	if (p_e->getType() != df::MSE_EVENT) {
		return 0;
	}
	const df::EventMouse* p_me = dynamic_cast<const df::EventMouse*>(p_e);
	if (mouseOverButton(p_me)) {
		setColor(m_highlight_color);
		if (p_me->getMouseAction() == df::EventMouseAction::CLICKED) {
			callback();
		}
	}
	setColor(m_default_color);
	return 1;
}

void df::Button::setHighlightColor(df::Color new_highlight_color) {
	m_highlight_color = new_highlight_color;
}

df::Color df::Button::getHighlightColor() const {
	return m_highlight_color;
}

void df::Button::setDefaultColor(df::Color new_default_color) {
	m_default_color = new_default_color;
}

df::Color df::Button::setDefaultColor() const {
	return m_default_color;
}

bool df::Button::mouseOverButton(const df::EventMouse* p_e) const {
	int width = getViewString().length(), height = 1;
	if (getBorder()) {
		width += 4;
		height += 2;
	}
	df::Box b(df::Vector(getPosition().getX() - width / 2, getPosition().getY() - height - 2), width, height);
	return df::boxContainsPosition(b, p_e->getMousePosition());
}