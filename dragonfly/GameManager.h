/**
	@file GameManager.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "Manager.h"
#include "SaveGame.h"

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
		bool m_enable_input; // True if input should be processed.
		int m_step_count; // Count of game loop iterations.
		std::string savePathTemplate;
		std::string saveExt;
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
		// Get if input is enabled.
		bool getEnableInput();
		// Set if input is enabled.
		void setEnableInput(bool new_enable_input);
		// Save a SaveGame object to an assigned slot
		// Return number of bytes written. -1 if write error, -2 if file error.
		int saveGameToSlot(SaveGame* saveGame, int slot);
		// Return a SaveGame object for the given slot. Empty SaveGame object if no save game found.
		SaveGame loadGameFromSlot(int slot);
	};
} // end of namespace df
#endif // __GAME_MANAGER_H__
