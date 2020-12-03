/**
	@file EnemySlime.h
	@author David Mahany (djmahany@wpi.edu)
*/
#pragma once

#ifndef __ENEMY_SLIME_H__
#define __ENEMY_SLIME_H__

#include "EnemyMaster.h"

class EnemySlime : public EnemyMaster {
private:
	int jumpCooldown = 0;
public:
	EnemySlime();

	virtual int eventHandler(const df::Event* ev);

	void resetJumpCooldown();
};
#endif // __ENEMY_SLIME_H__