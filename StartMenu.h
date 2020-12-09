/**
	@file StartMenu.h
	@author David Mahany (djmahany@wpi.edu)
*/
#pragma once

#include "dragonfly/ViewObject.h"

#include "Player.h"

class StartMenu : public df::ViewObject {
private:
	Player* player;

	void step(void);
public:
	StartMenu(Player* pl);
	~StartMenu();
	int eventHandler(const df::Event* p_e);
	int draw();
};