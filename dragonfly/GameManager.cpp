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

// System includes.
#include <Windows.h>

df::GameManager::GameManager() {
	setType("GameManager");
	m_game_over = false;
	m_step_count = 0;
}

df::GameManager::GameManager(GameManager const&) {
	setType("GameManager");
	m_game_over = false;
	m_step_count = 0;
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
	if (FM.isStarted()) {
		FM.shutDown();
	}
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
	while (!m_game_over) {
		m_step_count++;

		clock.delta(); // Reset frame clock.

		IM.getInput(); // Poll and dispatch input events.
		WM.update(m_step_count); // Update world objects and delete pending objects.

		if (!FM.isStarted()) {
			if (FM.startUp()) {
				writeLog("ERROR", "Error starting FloorManager.");
				setGameOver();
				return;
			}
		}
		
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