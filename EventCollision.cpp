/**
	Collision event.
	@file EventCollision.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "EventCollision.h"

df::EventCollision::EventCollision() {
	setType(df::COLLISION_EVENT);
	df::Vector v;
	m_pos = v;
	m_p_obj1 = NULL;
	m_p_obj2 = NULL;
}

df::EventCollision::EventCollision(df::Object* p_o1, df::Object* p_o2, df::Vector p) {
	setType(df::COLLISION_EVENT);
	m_pos = p;
	m_p_obj1 = p_o1;
	m_p_obj2 = p_o2;
}

void df::EventCollision::setObject1(df::Object* p_new_o1) {
	m_p_obj1 = p_new_o1;
}

df::Object* df::EventCollision::getObject1() const {
	return m_p_obj1;
}

void df::EventCollision::setObject2(df::Object* p_new_o2) {
	m_p_obj1 = p_new_o2;
}

df::Object* df::EventCollision::getObject2() const {
	return m_p_obj2;
}

void df::EventCollision::setPosition(df::Vector new_pos) {
	m_pos = new_pos;
}

df::Vector df::EventCollision::getPosition() const {
	return m_pos;
}