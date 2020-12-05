#include "ViewObject.h"

// Engine includes.
#include "DisplayManager.h"
#include "WorldManager.h"
#include "EventView.h"
#include "utility.h"

df::ViewObject::ViewObject() {
	setIsViewObject();
	setSolidness(df::Solidness::SPECTRAL);
	setAltitude(MAX_ALTITUDE);
	setType("ViewObject");
	
	setValue(0);
	setDrawValue();
	setBorder(true);
	setLocation(df::ViewObjectLocation::TOP_CENTER);
	setColor(df::Color::UNDEFINED_COLOR);
	
	registerInterest(df::VIEW_EVENT);
}

int df::ViewObject::draw() {
	int res = 0;
	df::Vector pos = df::worldToView(getPosition());
	std::string tmp_str = getViewString() + " " + df::toString(m_value);
	if (m_border) {
		pos.setY(pos.getY() - (int)df::charHeight());
		tmp_str = "| " + tmp_str + " |";
		std::string tmp_top = "";
		for (int i = 0; i < tmp_str.length() - 2; i++) {
			tmp_top += "-";
		}
		res = DM.drawString(pos, tmp_top, df::Justification::CENTER_JUSTIFIED, getColor());
		if (res == -1) {
			return -1;
		}
		pos.setY(pos.getY() + (int)df::charHeight());
	}
	DM.drawString(pos, tmp_str, df::Justification::CENTER_JUSTIFIED, getColor());
	if (m_border) {
		pos.setY(pos.getY() + (int)df::charHeight());
		std::string tmp_bottom = "";
		for (int i = 0; i < tmp_str.length() - 2; i++) {
			tmp_bottom += "-";
		}
		res = DM.drawString(pos, tmp_bottom, df::Justification::CENTER_JUSTIFIED, getColor());
		if (res == -1) {
			return -1;
		}
	}
	return 0;
}

int df::ViewObject::eventHandler(const Event* p_e) {
	if (p_e->getType() == VIEW_EVENT) {
		const df::EventView* p_ve = static_cast<const df::EventView*>(p_e);
		if (p_ve->getTag() == getViewString()) {
			if (p_ve->getDelta()) {
				setValue(getValue() + p_ve->getValue());
			}
			else {
				setValue(p_ve->getValue());
			}
		}
		return 1;
	}
	return df::Object::eventHandler(p_e);
}

void df::ViewObject::setLocation(df::ViewObjectLocation new_location) {
	df::Object::setPosition(df::viewToWorld(df::Vector(WM.getView().getHorizontal() * ((int)((int)(new_location) % 3) + 1) / 6, (WM.getView().getVertical() * ((int)((int)(new_location) % 3 ) + 1) / 6) + (-1 * !getBorder()))));
	m_location = new_location;
}

df::ViewObjectLocation df::ViewObject::getLocation() const {
	return m_location;
}

void df::ViewObject::setDrawValue(bool new_draw_value) {
	m_draw_value = new_draw_value;
}

bool df::ViewObject::getDrawValue() const {
	return m_draw_value;
}

void df::ViewObject::setValue(int new_value) {
	m_value = new_value;
}

int df::ViewObject::getValue() const {
	return m_value;
}

void df::ViewObject::setBorder(bool new_border) {
	if (m_border != new_border) {
		m_border = new_border;
		setLocation(getLocation());
	}
}

bool df::ViewObject::getBorder() const {
	return m_border;
}

void df::ViewObject::setColor(df::Color new_color) {
	m_color = new_color;
}

df::Color df::ViewObject::getColor() const {
	return m_color;
}

void df::ViewObject::setViewString(std::string new_view_string) {
	m_view_string = new_view_string;
}

std::string df::ViewObject::getViewString() const {
	return m_view_string;
}