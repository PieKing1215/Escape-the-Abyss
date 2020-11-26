/**
	Frame.
	@file Frame.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "Frame.h"

// Engine includes.
#include "DisplayManager.h"
#include "LogManager.h"

df::Frame::Frame() {
	m_width = 0;
	m_height = 0;
	m_frame_str = "";
	m_transparency = '\0';
}

df::Frame::Frame(int new_width, int new_height, std::string frame_str) {
	m_width = new_width;
	m_height = new_height;
	m_frame_str = frame_str;
	m_transparency = '\0';
}

df::Frame::Frame(int new_width, int new_height, std::string frame_str, char new_transparency) {
	m_width = new_width;
	m_height = new_height;
	m_frame_str = frame_str;
	m_transparency = new_transparency;
}

void df::Frame::setWidth(int new_width) {
	m_width = new_width;
}

int df::Frame::getWidth() const {
	return m_width;
}

void df::Frame::setHeight(int new_height) {
	m_height = new_height;
}

int df::Frame::getHeight() const {
	return m_height;
}

void df::Frame::setString(std::string new_frame_str) {
	m_frame_str = new_frame_str;
}

std::string df::Frame::getString() const {
	return m_frame_str;
}

void df::Frame::setTransparency(char new_transparency) {
	m_transparency = new_transparency;
}

char df::Frame::getTransparency() const {
	return m_transparency;
}

int df::Frame::draw(df::Vector position, df::Color color, char transparent) const {
	if (!DM.getWindow()) {
		LM.writeLog("ERROR", "Frame", "Cannot draw. No window.");
		return -1;
	}
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			if (!transparent || m_frame_str[x + (y * getWidth())] != transparent) {
				// Only draw if the character is not the transparent character or there is no transparent character.
				if (DM.drawCh(position + df::Vector(x, y), m_frame_str[x + (y * getWidth())], color) == -1) {
					LM.writeLog("ERROR", "Frame", "Error drawing char %d %d.", x, y);
					return -1;
				}
			}
		}
	}
	return 0;
}