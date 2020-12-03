#pragma once

#include "EnemyMaster.h"

class EnemyBat : public EnemyMaster {

    float randomOffset;

public:
    EnemyBat();

    virtual int eventHandler(const df::Event* ev);
};