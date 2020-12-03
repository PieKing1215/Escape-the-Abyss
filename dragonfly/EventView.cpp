#include "EventView.h"

df::EventView::EventView() {
	setType(VIEW_EVENT);
	m_tag = "";
	m_value = 0;
	m_delta = false;
}

df::EventView::EventView(std::string new_tag, int new_value, bool new_delta) {
	setType(VIEW_EVENT);
	m_tag = new_tag;
	m_value = new_value;
	m_delta = new_delta;
}

void df::EventView::setTag(std::string new_tag) {
	m_tag = new_tag;
}

std::string df::EventView::getTag() const {
	return m_tag;
}

void df::EventView::setValue(int new_value) {
	m_value = new_value;
}

int df::EventView::getValue() const {
	return m_value;
}

void df::EventView::setDelta(bool new_delta) {
	m_delta = new_delta;
}

bool df::EventView::getDelta() const {
	return m_delta;
}