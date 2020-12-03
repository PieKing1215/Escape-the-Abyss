#pragma once

#include "EnemyMaster.h"

class EnemySlime : public EnemyMaster {

    int jumpCooldown = 0;

public:
    EnemySlime();

    virtual int eventHandler(const df::Event* ev);

    void resetJumpCooldown();
};