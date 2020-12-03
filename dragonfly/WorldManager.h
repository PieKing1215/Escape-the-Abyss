/**
	@file WorldManager.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __WORLD_MANAGER_H__
#define __WORLD_MANAGER_H__

// Engine includes.
#include "Manager.h"
#include "ObjectList.h"
#include "Vector.h"
#include "SceneGraph.h"

// Two-letter acronym for easier access to manager.
#define WM df::WorldManager::getInstance()

namespace df {
	const float GRAVITY = 0.04; // Velocity in positive y (down) added every frame
	class WorldManager : public Manager {
	private:
		WorldManager();                 // Private since a singleton.
		WorldManager(WorldManager const&);  // Don't allow copy.
		void operator=(WorldManager const&); // Don't allow assignment.
		Box boundary; // World boundary.
		Box view; // Player view of game world.
		Object* p_view_following; // Object view is following.
		Vector view_slack;
		ObjectList m_deletions; // Objects to delete.
		SceneGraph scene_graph; // Storage for all Objects.
	public:
		// Get the one and only instance of the WorldManager.
		static WorldManager& getInstance();

		// Startup game world (initialize everything to empty).
		// Return 0.
		int startUp();

		// Shutdown game world (delete all game world Objects).
		void shutDown();

		// Insert Object into world.
		// Return 0 if ok, else -1.
		int insertObject(Object* p_o);

		// Remove Object from world.
		// Return 0 if ok, else -1.
		int removeObject(Object* p_o);

		// Return list of all Objects in world.
		ObjectList getAllObjects() const;

		// Indicate Object is to be deleted at start of next game loop.
		// Return 0 if ok, else -1.
		int markForDelete(Object* p_o);

		// Return all objects with the indicated type
		ObjectList objectsOfType(std::string type) const;

		// Update world.
		// Delete Objects marked for deletion.
		// Update positions of Objects based on their velocities, generating collisions, as appropriate.
		void update(int step_count);

		// Draw all Objects in view.
		// Draw bottom up, from 0 to MAX_ALTITUDE.
		void draw();

		// Move Object. 
		// If collision with solid, send collision events.
		// If no collision with solid, move ok else don't move Object.
		// If Object is Spectral, move ok.
		// If move ok, adjust view if following this Object.
		// If moved from inside world boundary to outside, generate EventOut.
		// Return 0 if move ok, else -1 if collision with solid.
		int moveObject(Object* p_o, Vector where);

		// Return list of Objects collideding.
		// Collisions only with solid Objects.
		// Does not consider if p_o is solid or not.
		ObjectList getCollisions(const Object* p_o) const;
		ObjectList getCollisions(const Object* p_o, Vector where) const;

		// Dispatch event to all interested Objects.
		// Return count of number of events sent.
		int onEvent(const Event* p_event) const;

		// Set game world boundary.
		void setBoundary(Box new_boundary);

		// Get game world boundary.
		Box getBoundary() const;

		// Set player view of game world.
		void setView(Box new_view);

		// Get player view of game world.
		Box getView() const;

		// Set view to center window on position view_pos.
		// View edge will not go beyong world boundary.
		void setViewPosition(Vector view_pos);

		// Set view to center window on object.
		// Set to NULL to stop following.
		// If p_new_view_following not valid, return -1. 0 otherwise.
		int setViewFollowing(Object* p_new_view_following);

		void setViewSlack(Vector new_view_slack);

		Vector getViewSlack() const;

		// Return reference to the SceneGraph.
		SceneGraph getSceneGraph() const;

		// Attempt to find a location to move the object so it won't have collisions.
		// Returns the deltaPosition vector of a posible move location. Returns empty vector on failure to find a location.
		Vector attemptMove(Object* p_o, int max_out = 10); // Find a location within a square. Default is 5 units to each side.
		Vector attemptMoveInRadius(Object* p_o, int radius); // Find a location with a line of a square.
	};

} // end of namespace df
#endif // __WORLD_MANAGER_H__
