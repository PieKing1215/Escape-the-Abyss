/**
	Animation.
	@file Animation.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "Animation.h"

// Engine includes.
#include "DisplayManager.h"

df::Animation::Animation() {
	clearSprite();
}

void df::Animation::setSprite(Sprite* p_new_sprite) {
	m_p_sprite = p_new_sprite;
	setIndex(0);
	setSlowdownCount(p_new_sprite->getSlowdown());
	setName(p_new_sprite->getLabel());
}

void df::Animation::clearSprite() {
	m_p_sprite = NULL;
	setIndex(0);
	setSlowdownCount(0);
	setName("");

}

df::Sprite* df::Animation::getSprite() const {
	return m_p_sprite;
}

void df::Animation::setName(std::string new_name) {
	m_name = new_name;
}

std::string df::Animation::getName() const {
	return m_name;
}

void df::Animation::setIndex(int new_index) {
	m_index = new_index;
}

int df::Animation::getIndex() const {
	return m_index;
}

void df::Animation::setSlowdownCount(int new_slowdown_count) {
	m_slowdown_count = new_slowdown_count;
}

int df::Animation::getSlowdownCount() const {
	return m_slowdown_count;
}

int df::Animation::draw(Vector position) {
	if (!m_p_sprite) {
		return 0;
	}
	int index = getIndex();
	int pass = m_p_sprite->draw(index, position);
	if (pass == -1) {
		return -1;
	}
	if (getSlowdownCount() == -1) {
		return 0;
	}
	int count = getSlowdownCount() + 1;
	if (count >= m_p_sprite->getSlowdown()) {
		count = 0;
		index++;
		if (index >= m_p_sprite->getFrameCount()) {
			index = 0;
		}
		setIndex(index);
	}
	setSlowdownCount(count);
	return 0;
}

df::Box df::Animation::getBox() const {
	float x = 0, y = 0;
	if (m_p_sprite) {
		x = m_p_sprite->getWidth();
		y = m_p_sprite->getHeight();
	}
	return df::Box(df::Vector(-1.0 * x / 2.0, -1.0 * y / 2.0), x, y);
}