/**
	Basic flying enemy.
	@file EnemyBat.cpp
	@author David Mahany (djmahany@wpi.edu)
*/

#include "EnemyBat.h"

// Engine includes.
#include "dragonfly/WorldManager.h"
#include "dragonfly/ResourceManager.h"
#include "dragonfly/EventStep.h"
#include "dragonfly/utility.h"

EnemyBat::EnemyBat() {
    setType("Bat");
	randomOffset = rand() % 1000; // not important enough to use a good rng so just use rand
    setSprite("bat");

    // make the hitbox smaller so it can't hit the player from as far away
    auto b = getBox();
    b = df::Box(df::Vector(b.getCorner().getX() + 0.5f, b.getCorner().getY() + 0.25f), b.getHorizontal() - 1.0f, b.getVertical() - 0.5f);
    setBox(b);
}

EnemyBat::~EnemyBat() {
    RM.getSound("bat_die")->play();
}

int EnemyBat::eventHandler(const df::Event* ev) {

    if(ev->getType() == df::STEP_EVENT) {
        // layer a bunch of sines with arbitrary multipliers for easy "random" movement
        // randomOffset shifts the sines around a bit so that different bats have different movement
        long time = df::getTime();
        float dx = sin((time + randomOffset * 1.0) / 310.1) / 10.0f + sin((time + randomOffset * 2.0) / 500.1) / 10.0f + sin((time + randomOffset * 7.0) / 221.6) / 20.0f + sin((time + randomOffset * 4.0) / 104.2) / 20.0f;
        float dy = sin((time + randomOffset * 1.1) / 580.1) / 12.0f + sin((time + randomOffset * 5.0) / 377.3) / 12.0f + sin((time + randomOffset * 2.0) / 202.7) / 20.0f + sin((time + randomOffset * 3.0) / 82.4) / 10.0f;

        // only scan for the player once in a while (helps with performance)
        scanCooldown--;
        if(scanCooldown <= 0) {
            pxd = 0.0f;
            pyd = 0.0f;
            nearPlayer = false;
            scanCooldown = 15;

            df::ObjectList ol = WM.getSceneGraph().activeObjects();
            df::ObjectListIterator toUpdate(&ol);
            toUpdate.first();
            std::string x = "";
            while(!toUpdate.isDone() && toUpdate.currentObject()) {
                if(toUpdate.currentObject()->getType() == "Player") {
                    float dist = (getPosition() - toUpdate.currentObject()->getPosition()).getMagnitude();
                    // if in range
                    if(dist < 32) {
                        // calculate direction to player
                        float pdx = getPosition().getX() - toUpdate.currentObject()->getPosition().getX();
                        float pdy = getPosition().getY() - toUpdate.currentObject()->getPosition().getY();

                        df::Vector mov(pdx, pdy);
                        mov.normalize();

                        // move towards player (faster horizontally than vertically)
                        pxd = -mov.getX() / 2.0f;
                        pyd = -mov.getY() / 4.0f;

                        nearPlayer = true;
                    }
                }
                toUpdate.next();
            }
        }

        if(nearPlayer) {
            dx += pxd;
            dy += pyd;
        }

        setVelocity({dx / 3.0f, dy / 3.0f});
    }

    return 0;
}
