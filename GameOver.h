/**
	@file GameOver.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#include "dragonfly/ViewObject.h"

class GameOver : public df::ViewObject {
private:
	int time_to_live = 0;
	void step(void);
public:
	GameOver();
	~GameOver();
	int eventHandler(const df::Event* p_e);
	int draw();
};