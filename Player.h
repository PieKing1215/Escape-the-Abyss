/**
	@file Player.h
	@author David Mahany (djmahany@wpi.edu)
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
	float yOffset = 0;

public:
	PlayerAttack(Player* pl, bool left, float yOffset);

	virtual int eventHandler(const df::Event* p_e);

	virtual int draw();

};

class Player : public df::Object {

	int attackCooldown = 40;
	float walkCycle = 0.0f;

	int invulnerability = 60;

	float maxHealth;
	float health;

	bool playStartAnim = true;
	bool startAnimFire = false;
	int startTickCounter = 0;
	bool playEndAnim = false;
	bool endAnimFire = false;

	bool animStartFlag = false;

public:

	Player();

	virtual int eventHandler(const df::Event* p_e);

	virtual int draw();

	void tickMovement();
	void jump();
	void endJump();

	void damage(float damage, df::Vector source);
	void die();

	void endAnim();

	void startFlag();
};

#endif // __PLAYER__
