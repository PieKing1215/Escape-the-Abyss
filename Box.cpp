/**
	Box.
	@file Box.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "Box.h"

df::Box::Box() {
	m_corner = df::Vector();
	m_horizontal = 0;
	m_vertical = 0;
}

df::Box::Box(df::Vector init_corner, float init_horizontal, float init_vertical) {
	m_corner = init_corner;
	m_horizontal = init_horizontal;
	m_vertical = init_vertical;
}

void df::Box::operator=(const df::Box& other) {
	m_corner = other.getCorner();
	m_horizontal = other.getHorizontal();
	m_vertical = other.getVertical();
}

void df::Box::setCorner(df::Vector new_corner) {
	m_corner = new_corner;
}

df::Vector df::Box::getCorner() const {
	return m_corner;
}

void df::Box::setHorizontal(float new_horizontal) {
	m_horizontal = new_horizontal;
}

float df::Box::getHorizontal() const {
	return m_horizontal;
}

void df::Box::setVertical(float new_vertical) {
	m_vertical = new_vertical;
}

float df::Box::getVertical() const {
	return m_vertical;
}