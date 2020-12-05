/**
	@file Object.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __OBJECT_H__
#define __OBJECT_H__

// Engine includes.
#include "Animation.h"
#include "Box.h"
#include "Event.h"
#include "Sprite.h"
#include "Vector.h"

namespace df {

	const int MAX_OBJ_EVENTS = 100;

	// Types of solidness of Object.
	enum class Solidness {
		HARD,       // Object causes collisions and impedes.
		SOFT,       // Object causes collision, but doesn't impede.
		SPECTRAL,   // Object doesn't cause collisions.
	};
	// Ways to handle overlap on spawn.
	enum class OverlapHandle {
		DO_NOT_SPAWN, // Do not spawn impeded object
		ATTEMPT_TO_MOVE, // Attempt to move the impeded object with a square around the problematic location.
		SPAWN_ALWAYS // Spawn anyways. You shouldn't use this.
	};

	class Object {

	private:
		int m_id; // Unique game engine defined identifier.
		std::string m_type; // Game-programmer defined identification.
		Box m_box; // Box for sprite boundary & collisions.
		Vector m_position; // Position in game world.
		Vector m_direction; // Direction vector.
		float m_speed; // Object speed in direction.
		std::string sprite_name; // Sprite name in ResourceManager.
		Animation m_animation; // Animation associated with Object.
		int m_altitude; // 0 to MAX_ALTITUDE (higher drawn on top).
		Solidness m_solidness; // Solidness state of Object.
		bool m_no_soft; // Treat collisions with SOFT objects the same as HARD objects if true
		int event_count; // The number of events that can be received by this object.
		std::string event_name[MAX_OBJ_EVENTS]; // The events that can be received by this object.
		bool is_active; // Don't update if not active
		bool is_visible; // Don't draw if not visible
		OverlapHandle overlapHandle; // How to treat this object on spawn
		bool has_gravity; // Is affected by gravity
		bool m_view_object;
	protected:
		// Writes to log with the object type and id being the reporter
		int writeLog(std::string warn, const char* fmt, ...) const;
	public:
		// Construct Object. 
		// Set default parameters and add to game world (WorldManager).
		Object();

		// Destroy object, removing itself from game world (WorldManager).
		virtual ~Object();

		// Set Object id.
		void setId(int new_id);

		// Get Object id.
		int getId() const;

		// Set type identifier of Object.
		void setType(std::string new_type);

		// Get type identifier of Object.
		std::string getType() const;

		// Set position of Object.
		virtual void setPosition(Vector new_position);

		// Get position of Object.
		Vector getPosition() const;

		// Handle event.
		// Base class ignores everything.
		// Return 0 if ignored, else 1.
		virtual int eventHandler(const Event* p_event);

		// Return True if Object is HARD or SOFT, else false.
		bool isSolid() const;

		// Set solidness of Object, with checks for consistency.  
		// Return 0 if ok, else -1.
		int setSolidness(Solidness new_solid);

		// Return solidness of Object.
		Solidness getSolidness() const;

		// Set altitude of Object, with checks for range [0, MAX_ALTITUDE].
		// Return 0 if ok, else -1.
		int setAltitude(int new_altitude);

		// Return altitude of Object.
		int getAltitude() const;

		// Set speed of Object.
		void setSpeed(float new_speed);

		// Get speed of Object.
		float getSpeed() const;

		// Set direction of Object.
		void setDirection(Vector new_direction);

		// Get direction of Object.
		Vector getDirection() const;

		// Set direction and speed of Object.
		void setVelocity(Vector new_velocity);

		// Get velocity of Object based on direction and speed.
		Vector getVelocity() const;

		// Predict Object position based on speed and direction.
		// Return predicted position.
		Vector predictPosition();

		// Set if Object has gravity.
		void hasGravity(bool new_has_gravity);

		// Get if Object has gravity
		bool hasGravity() const;

		// Set bounding box of Object.
		void setBox(Box new_box);

		// Get bounding box of Object.
		Box getBox() const;

		// Set Sprite for this Object to animate.
		// It is imperetive that you call this as the last modifier of the class constructor as this class also adds the object to the screen.
		// Return 0 if ok, else -1.
		int setSprite(std::string sprite_label);

		// Set Animation for this Object to new one.
		// Set bounding box to size of associated Sprite.
		void setAnimation(Animation new_animation);

		// Get Animation for this Object.
		Animation* getAnimation();

		// Draw Object Animation.
		virtual int draw();

		// Return no soft of Object
		void setNoSoft(bool new_no_soft);

		bool getNoSoft() const;

		// Indicate interest in event.
		// Return 0 if ok, else −1.
		// (Note, doesn’t check to see if Object is already registered.)
		int registerInterest(Object* p_o, std::string event_type);

		int registerInterest(std::string event_type);

		// Indicate no more interest in event.
		// Return 0 if ok, else −1.
		int unregisterInterest(Object* p_o, std::string event_type);

		// Set activeness of Object.
		// Return 0 if ok, else -1
		int setActive(bool active = true);

		// Return activeness of Object.
		bool isActive() const;

		// Set visibility of Object.
		// Return 0 if ok, else -1
		int setVisible(bool visible = true);

		// Return visibility of Object.
		bool isVisible() const;

		// Return overlapHandle of Object.
		OverlapHandle getOverlapHandle() const;

		// Try to move object so it isn't colliding
		bool tryToMove();

		bool isGrounded();

		void setIsViewObject(bool new_is_view_object = true);

		bool isViewObject();
	};
} // end of namespace df
#endif // __OBJECT_H__
