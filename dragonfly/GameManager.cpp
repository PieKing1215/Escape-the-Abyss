/**
	Game manager.
	@file GameManager.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "GameManager.h"

// Engine includes.
#include "DisplayManager.h"
#include "../FloorManager.h"
#include "InputManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "Clock.h"
#include "ObjectListIterator.h"
#include "EventStep.h"
#include "utility.h"

// System includes.
#include <Windows.h>
#include <fstream>

df::GameManager::GameManager() {
	setType("GameManager");
	m_game_over = false;
	m_step_count = 0;
	savePathTemplate = "saves/slot_";
	saveExt = ".dat";
}

df::GameManager::GameManager(GameManager const&) {
	setType("GameManager");
	m_game_over = false;
	m_step_count = 0;
	savePathTemplate = "saves/slot_";
	saveExt = ".dat";
}

void df::GameManager::operator=(GameManager const&) {

}

df::GameManager& df::GameManager::getInstance() {
	static GameManager gameManager;
	return gameManager;
}

int df::GameManager::startUp() {
	timeBeginPeriod(1);
	if (LM.startUp()) {
		return -1;
	}
	if (DM.startUp()) {
		writeLog("ERROR", "Error staring DisplayManager.");
		return -1;
	}
	if (WM.startUp()) {
		writeLog("ERROR", "Error starting WorldManager.");
		return -1;
	}
	if (IM.startUp()) {
		writeLog("ERROR", "Error starting InputManager.");
		return -1;
	}
	df::Manager::startUp();
	return 0;
}

void df::GameManager::shutDown() {
	m_game_over = true;
	timeEndPeriod(1);
	writeLog("", "Stopping managers.");
	IM.shutDown();
	WM.shutDown();
	DM.shutDown();
	LM.shutDown();
	df::Manager::shutDown();
}

void df::GameManager::run() {
	Clock clock;
	int adjust_time = 0;
	m_step_count = 0;
	writeLog("ALERT", "--------START GAME LOOP--------");
	if (!FM.isStarted()) {
		if (FM.startUp()) {
			writeLog("ERROR", "Error starting FloorManager.");
			setGameOver();
			return;
		}
	}
	while (!m_game_over) {
		m_step_count++;

		clock.delta(); // Reset frame clock.

		IM.getInput(); // Poll and dispatch input events.
		WM.update(m_step_count); // Update world objects and delete pending objects.
		
		WM.draw(); // Redraw frame.
		DM.swapBuffers(); // Prepare buffer for new frame.
		
		EventStep s;
		WM.onEvent(&s); // Dispatch step event.

		// Pause for a small amount of time to run game at 30 fps.
		int loop_time = clock.split();
		long int intended_sleep_time = FRAME_TIME_DEFAULT - loop_time - adjust_time;
		if (intended_sleep_time < 0) {
			intended_sleep_time = 0;
		}
		clock.delta();
		Sleep(intended_sleep_time);
		adjust_time = (clock.split() / 1000) - intended_sleep_time;
		if (adjust_time < 0) {
			adjust_time = 0;
		}
	}
	if (FM.isStarted()) {
		FM.shutDown();
	}
	WM.getAllObjects();
	writeLog("ALERT", "---------END GAME LOOP---------");
}

void df::GameManager::setGameOver(bool new_game_over) {
	m_game_over = new_game_over;
}

bool df::GameManager::getGameOver() const {
	return m_game_over;
}

int df::GameManager::getStepCount() const {
	return m_step_count;
}

int df::GameManager::saveGameToSlot(df::SaveGame* saveGame, int slot) {
	FILE* p_f;
	fopen_s(&p_f, (savePathTemplate + df::toString(slot) + saveExt).c_str(), "w"); // Open the save file for writing.
	if (p_f == NULL) {
		return -2;
	}
	std::string saveString = saveGame->getSaveString();
	int x = fprintf(p_f, (df::toString((int)saveString.size()) + "\n" + saveGame->getSaveString() + "end").c_str()); // Write saveGame's saveString
	fclose(p_f);
	return x;
}

df::SaveGame df::GameManager::loadGameFromSlot(int slot) {
	df::SaveGame* saveGame = new df::SaveGame();
	std::ifstream file((savePathTemplate + df::toString(slot) + saveExt).c_str());
	if (!file.good()) {
		writeLog("ERROR", "Error loading from save slot '%d'. Save does not exist.", slot);
		file.close();
		return *saveGame;
	}
	std::string s = df::getLine(&file);
	while (s != "end" && !s.empty()) {
		int split = s.find_first_not_of(':');
		saveGame->loadSaveString(s.substr(0, split), s.substr(split + 1, s.size() - (split + 1)));
		s = df::getLine(&file);
	}
	return *saveGame;
}