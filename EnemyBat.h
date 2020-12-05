/**
	@file EnemyBat.h
	@author David Mahany (djmahany@wpi.edu)
*/
#pragma once

#ifndef __ENEMY_BAT_H__
#define __ENEMY_BAT_H__

#include "EnemyMaster.h"

class EnemyBat : public EnemyMaster {
private:
	float randomOffset;
	bool nearPlayer = false;
	float pxd = 0.0f;
	float pyd = 0.0f;
	int scanCooldown = 15;
public:
	EnemyBat();

	virtual int eventHandler(const df::Event* ev);
};
#endif // __ENEMY_BAT_H__