/**
	@file GameManager.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "Manager.h"

// Two-letter acronym for easier access to manager.
#define GM df::GameManager::getInstance()

namespace df {
	// Default frame time (game loop time) in milliseconds (33 ms == 30 f/s).
	const int FRAME_TIME_DEFAULT = 33;
	class GameManager : public Manager {
	private:
		// Private since a singleton.
		GameManager();
		// Don't allow copy.
		GameManager(GameManager const&);
		// Don't allow assignment.
		void operator=(GameManager const&);
		bool m_game_over; // True if game loop should stop.
		int m_step_count; // Count of game loop iterations.
	public:
		// Get the singleton instance of the GameManager.
		static GameManager &getInstance();
		// Startup all GameManager services.
		int startUp();
		// Shut down GameManager services.
		void shutDown();
		// Run game loop.
		void run();
		// Set game over status to indicated value.
		// If true (default), will stop game loop.
		void setGameOver(bool new_game_over=true);
		// Get game over status.
		bool getGameOver() const;
		// Return game loop step count.
		int getStepCount() const;
	};
} // end of namespace df
#endif // __GAME_MANAGER_H__
