/**
	Object master.
	@file Object.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "Object.h"

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "EventStep.h"
#include "utility.h"

// System includes.
#include <stdarg.h>

static int counter = 0;

df::Object::Object() {
	m_id = counter;
	counter++;
	m_type = "Object";
	df::Vector v;
	m_position = v;
	m_direction = v;
	m_speed = 0;
	sprite_name = "";
	m_altitude = 0;
	m_solidness = df::Solidness::HARD;
	m_no_soft = false;
	m_animation = df::Animation();
	m_box = df::Box();
	event_count = 0;
	event_name;
	is_active = true;
	is_visible = true;
	overlapHandle = df::OverlapHandle::ATTEMPT_TO_MOVE;
	has_gravity = false;
	m_view_object = false;
	WM.registerInterest(this, df::STEP_EVENT);

	writeLog("", "Spawned. Awaiting sprite or manual insert for world insertion.");
}

df::Object::~Object() {
	WM.removeObject(this);
	for (int i = event_count - 1; i >= 0; i--) {
		unregisterInterest(this, event_name[i]);
	}
	writeLog("ALERT", "Die.");
}

void df::Object::setId(int new_id) {
	m_id = new_id;
}

int df::Object::getId() const {
	return m_id;
}

void df::Object::setType(std::string new_type) {
	m_type = new_type;
	writeLog("", "Renamed %s.", new_type.c_str());
}

std::string df::Object::getType() const {
	return m_type;
}

void df::Object::setPosition(Vector new_position) {
	m_position = new_position;
}

df::Vector df::Object::getPosition() const {
	return m_position;
}

int df::Object::eventHandler(const Event* p_event) {
	return 0;
}

bool df::Object::isSolid() const {
	return m_solidness != df::Solidness::SPECTRAL;
}

int df::Object::setSolidness(df::Solidness new_solid) {
	if (WM.getSceneGraph().updateSolidness(this, new_solid)) {
		return -1;
	}
	m_solidness = new_solid;
	return 0;
}

df::Solidness df::Object::getSolidness() const {
	return m_solidness;
}

int df::Object::setAltitude(int new_altitude) {
	if (WM.getSceneGraph().updateAltitude(this, new_altitude)) {
		return -1;
	}
	m_altitude = new_altitude;
	return 0;
}

int df::Object::getAltitude() const {
	return m_altitude;
}

void df::Object::setSpeed(float new_speed) {
	m_speed = new_speed;
}

float df::Object::getSpeed() const {
	return m_speed;
}

void df::Object::setDirection(Vector new_direction) {
	m_direction = new_direction;
}

df::Vector df::Object::getDirection() const {
	return m_direction;
}

void df::Object::setVelocity(df::Vector new_velocity) {
	m_speed = new_velocity.getMagnitude();
	m_direction = new_velocity;
	m_direction.normalize();
}

df::Vector df::Object::getVelocity() const {
	df::Vector v(m_direction.getX() * m_speed, m_direction.getY() * m_speed);
	return v;
}

void df::Object::hasGravity(bool new_has_gravity) {
	has_gravity = new_has_gravity;
}

bool df::Object::hasGravity() const {
	return has_gravity;
}

df::Vector df::Object::predictPosition() {
	df::Vector v = m_position + getVelocity();
	return (v);
}

void df::Object::setNoSoft(bool new_no_soft) {
	m_no_soft = new_no_soft;
}

bool df::Object::getNoSoft() const {
	return m_no_soft;
}

int df::Object::setSprite(std::string sprite_label) {
	std::string old_string = sprite_name;
	df::Sprite* p_sprite = RM.getSprite(sprite_label);
	if (!p_sprite) {
		writeLog("ERROR", "Error getting '%s' sprite.", sprite_label.c_str());
		return -1;
	}
	df::Sprite* old_sprite = m_animation.getSprite();
	m_animation.setSprite(p_sprite);
	setBox(m_animation.getBox());
	sprite_name = sprite_label;
	// If there are collisions after changing the sprite.
	/*if (WM.getCollisions(this).getCount() > 0) {
		writeLog("ALERT", "Error setting sprite '%s'. Collision on change. Attempting to move.", sprite_label.c_str());
		if (old_sprite) {
			if (!tryToMove()) {
				m_animation.setSprite(old_sprite);
				setBox(m_animation.getBox());
				sprite_name = old_string;
				writeLog("ERROR", "No nearby locations found. Reverted to '%s'.", old_string.c_str());
				return -1;
			}
		}
		else {
			if (!tryToMove()) {
				m_animation.clearSprite();
				setBox(m_animation.getBox());
				sprite_name = "";
				writeLog("ERROR", "No nearby locations found. Cleared sprite.");
				return -1;
			}
		}
	}*/
	writeLog("", "Sprite set to '%s'.", sprite_label.c_str());
	if (!old_sprite) {
		return WM.insertObject(this);
	}
	return 0;
}

void df::Object::setAnimation(Animation new_animation) {
	m_animation = new_animation;
}

df::Animation* df::Object::getAnimation() {
	return &m_animation;
}

void df::Object::setBox(df::Box new_box) {
	m_box = new_box;
}

df::Box df::Object::getBox() const {
	return m_box;
}

int df::Object::draw() {

	/*float x = getPosition().getX();
	float y = getPosition().getY();
	float corner_x = x + getBox().getCorner().getX();
	float corner_y = y + getBox().getCorner().getY();
	float horizontal = getBox().getHorizontal();
	float vert = getBox().getVertical();
	Vector ul(corner_x, corner_y);
	Vector ur(corner_x + horizontal, corner_y);
	Vector ll(corner_x, corner_y + vert);
	Vector lr(corner_x + horizontal, corner_y + vert);
	Vector mi(x, y);
	DM.drawCh(ul, '+', df::Color::WHITE);
	DM.drawCh(ur, '+', df::Color::WHITE);
	DM.drawCh(ll, '+', df::Color::WHITE);
	DM.drawCh(lr, '+', df::Color::WHITE);*/

	if (isVisible() && m_animation.getSprite()) {
		return m_animation.draw(getPosition() - df::Vector((m_animation.getSprite()->getWidth()) / 2.0f, (m_animation.getSprite()->getHeight()) / 2.0f) + df::Vector(0.5f, 0.5f));
	}
	return 0;
}

int df::Object::registerInterest(df::Object* p_o, std::string event_type) {
	if (event_count == df::MAX_OBJ_EVENTS) {
		return -1;
	}
	GM.registerInterest(this, event_type);
	event_name[event_count] = event_type;
	event_count++;
	return 0;
}

int df::Object::registerInterest(std::string event_type) {
	return registerInterest(this, event_type);
}

int df::Object::unregisterInterest(df::Object* p_o, std::string event_type) {
	for (int i = 0; i < event_count; i++) {
		if (event_name[i] == event_type) {
			if (event_type == df::STEP_EVENT) {
				GM.unregisterInterest(this, event_type);
			}
			else {
				WM.unregisterInterest(this, event_type);
			}
			for (int j = i; j < event_count - 1; j++) {
				event_name[j] = event_name[j + 1];
			}
			event_count--;
			return 0;
		}
	}
	return -1;
}

int df::Object::writeLog(std::string warn, const char* fmt, ...) const {
	va_list args;
	va_start(args, fmt);
	int x = LM.writeLog(warn, getType() + " " + df::toString(getId()), fmt, args);
	va_end(args);
	return x;
}

int df::Object::setActive(bool active) {
	if (WM.getSceneGraph().updateActive(this, active)) {
		return -1;
	}
	is_active = active;
	return 0;
}

bool df::Object::isActive() const {
	return is_active;
}

int df::Object::setVisible(bool visible) {
	if (WM.getSceneGraph().updateVisible(this, visible)) {
		return -1;
	}
	is_visible = visible;
	return 0;
}

bool df::Object::isVisible() const {
	return is_visible;
}

df::OverlapHandle df::Object::getOverlapHandle() const {
	return overlapHandle;
}

bool df::Object::tryToMove() {
	float r = getBox().getHorizontal();
	if (getBox().getVertical() > r) {
		r = getBox().getVertical();
	}
	const df::Vector v = WM.attemptMove(this, r + 1);
	if (getPosition() == v) {
		return false;
	}
	setPosition(v);
	if (WM.getCollisions(this).getCount() > 0) {
		return -1;
	}
	writeLog("", "Location nearby found. Moved to %f %f", df::toString(v));
	return true;
}

bool df::Object::isGrounded() {
	// probably on the ground if we would collide with something if we moved slightly downwards

	auto obj = WM.getCollisions(this, getPosition() + df::Vector(0, 0.05f));
	df::ObjectListIterator li(&obj);
	li.first();
	while(!li.isDone()) {
		if(li.currentObject()->getSolidness() == df::Solidness::HARD) return true;
		li.next();
	}
	return false;
}

void df::Object::setIsViewObject(bool new_is_view_object) {
	m_view_object = new_is_view_object;
}

bool df::Object::isViewObject() {
	return m_view_object;
}
