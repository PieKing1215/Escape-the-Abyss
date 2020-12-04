/**
	@file Player.h
	@author
*/
#pragma once

#include "dragonfly/Object.h"

#ifndef __PLAYER__
#define __PLAYER__

class Player;

class PlayerAttack : public df::Object {
	int lifetime;
	Player* player;
	bool left;

public:
	PlayerAttack(Player* pl, bool left);

	virtual int eventHandler(const df::Event* p_e);

	virtual int draw();

};

class Player : public df::Object {

	int attackCooldown = 40;
	float walkCycle = 0.0f;

	int invulnerability = 60;

	float maxHealth;
	float health;

public:

	Player();

	virtual int eventHandler(const df::Event* p_e);

	virtual int draw();

	void tickMovement();
	void jump();
	void endJump();

	void damage(float damage, df::Vector source);
	void die();

};

#endif // __PLAYER__
