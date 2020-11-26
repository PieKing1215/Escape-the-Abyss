/**
	Vector data type.
	@file Vector.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "Vector.h"

// System includes.
#include <cmath>

df::Vector::Vector(float init_x, float init_y) {
	m_x = init_x;
	m_y = init_y;
}

df::Vector::Vector() {
	m_x = 0;
	m_y = 0;
}

void df::Vector::setX(float new_x) {
	m_x = new_x;
}

float df::Vector::getX() const {
	return m_x;
}

void df::Vector::setY(float new_y) {
	m_y = new_y;
}

float df::Vector::getY() const {
	return m_y;
}

void df::Vector::setXY(float new_x, float new_y) {
	setX(new_x);
	setY(new_y);
}

void df::Vector::normalize() {
	float magnitude = getMagnitude();
	if (magnitude > 0) {
		m_x /= magnitude;
		m_y /= magnitude;
	}
}

void df::Vector::scale(float s) {
	m_x *= s;
	m_y *= s;
}

float df::Vector::getMagnitude() const {
	return ((float)sqrt(pow(m_x, 2) + pow(m_y, 2)));
}

void df::Vector::operator=(const Vector& other) {
	setXY(other.getX(), other.getY());
}

bool df::Vector::operator==(const Vector& other) const {
	return (m_x == other.getX() && m_y == other.getY());
}

bool df::Vector::operator==(const float& other) const {
	return (m_x == other && m_y == other);
}

bool df::Vector::operator!=(const Vector& other) const {
	return (m_x != other.getX() || m_y != other.getY());
}

bool df::Vector::operator!=(const float& other) const {
	return (m_x != other || m_y != other);
}

df::Vector df::Vector::operator+(const Vector& other) const {
	return df::Vector(m_x + other.getX(), m_y + other.getY());
}

df::Vector df::Vector::operator-(const Vector& other) const {
	return df::Vector(m_x - other.getX(), m_y - other.getY());
}

df::Vector df::Vector::operator*(const Vector& other) const {
	return df::Vector(m_x * other.getX(), m_y * other.getY());
}

df::Vector df::Vector::operator/(const Vector& other) const {
	if (other.getX() == 0 || other.getY() == 0) {
		return *this;
	}
	return df::Vector(m_x / other.getX(), m_y / other.getY());
}

df::Vector df::Vector::operator+(const float& other) const {
	return df::Vector(m_x + other, m_y + other);
}

df::Vector df::Vector::operator-(const float& other) const {
	return df::Vector(m_x - other, m_y - other);
}

df::Vector df::Vector::operator*(const float& other) const {
	return df::Vector(m_x * other, m_y * other);
}

df::Vector df::Vector::operator/(const float& other) const {
	if (other == 0) {
		return *this;
	}
	return df::Vector(m_x / other, m_y / other);
}