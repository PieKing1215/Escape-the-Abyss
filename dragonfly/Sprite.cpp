/**
	Sprite master with animations.
	@file Sprite.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "Sprite.h"

// Engine includes.
#include "LogManager.h"

// System includes.
#include <stdarg.h>

df::Sprite::Sprite(int max_frames) {
	m_width = 0;
	m_height = 0;
	m_max_frame_count = max_frames;
	m_frame_count = 0;
	m_color = df::COLOR_DEFAULT;
	m_frame = new Frame[max_frames];
	m_label = "";
	m_transparent = '\0';
}

df::Sprite::~Sprite() {
	if (!m_frame) {
		delete[] m_frame;
	}
}

void df::Sprite::setWidth(int new_width) {
	m_width = new_width;
}

int df::Sprite::getWidth() const {
	return m_width;
}

void df::Sprite::setHeight(int new_height) {
	m_height = new_height;
}

int df::Sprite::getHeight() const {
	return m_height;
}

void df::Sprite::setColor(df::Color new_color) {
	m_color = new_color;
}

df::Color df::Sprite::getColor() const {
	return m_color;
}

int df::Sprite::getFrameCount() const {
	return m_max_frame_count;
}

int df::Sprite::addFrame(df::Frame new_frame) {
	if (m_frame_count >= m_max_frame_count) {
		writeLog("ERROR", "Error adding frame. Frame array full.");
		return -1;
	}
	*(m_frame + m_frame_count) = new_frame;
	m_frame_count++;
	return 0;
}

df::Frame df::Sprite::getFrame(int frame_number) const {
	if (frame_number < 0 || frame_number >= m_frame_count) {
		df::Frame f;
		return f;
	}
	return *(m_frame + frame_number);
}

void df::Sprite::setLabel(std::string new_label) {
	m_label = new_label;
}

std::string df::Sprite::getLabel() const {
	return m_label;
}

void df::Sprite::setSlowdown(int new_sprite_slowdown) {
	m_slowdown = new_sprite_slowdown;
}

int df::Sprite::getSlowdown() const {
	return m_slowdown;
}

void df::Sprite::setTransparent(char new_transparent) {
	m_transparent = new_transparent;
}

char df::Sprite::getTransparent() const {
	return m_transparent;
}

int df::Sprite::draw(int frame_number, df::Vector position) const {
	if (m_frame[frame_number].draw(position, getColor(), getTransparent()) == -1) {
		writeLog("ERROR", "Error drawing sprite frame %d", frame_number);
	}
	return 0;
}

int df::Sprite::writeLog(std::string warn, const char* fmt, ...) const {
	va_list args;
	va_start(args, fmt);
	int x = LM.writeLog(warn, "Sprite '" + getLabel() + "'", fmt, args);
	va_end(args);
	return x;
}