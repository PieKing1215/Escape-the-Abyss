/**
	@file Player.h
	@author
*/
#pragma once

#include "Object.h"

#ifndef __PLAYER__
#define __PLAYER__

class Player : public df::Object {

	float walkCycle = 0.0f;

public:

	Player();

	virtual int eventHandler(const df::Event* p_e);

	virtual int draw();

	bool isGrounded();

	void tickMovement();
	void jump();
	void endJump();

};

#endif // __PLAYER__
