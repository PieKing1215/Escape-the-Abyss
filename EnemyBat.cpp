#include "EnemyBat.h"

#include "EventStep.h"

#include "utility.h"

#include "WorldManager.h"

EnemyBat::EnemyBat() : EnemyMaster() {
    setType("Bat");
    setSprite("bat");

    auto b = getBox();
    b = df::Box(df::Vector(b.getCorner().getX() + 0.5f, b.getCorner().getY() + 0.25f), b.getHorizontal() - 1.0f, b.getVertical() - 0.5f);
    setBox(b);

    registerInterest(df::STEP_EVENT);

    // not important enough to use a good rng so just use rand
    randomOffset = rand() % 1000;
}

int EnemyBat::eventHandler(const df::Event* ev) {

    if(ev->getType() == df::STEP_EVENT) {
        // layer a bunch of sines with arbitrary multipliers for easy "random" movement
        // randomOffset shifts the sines around a bit so that different bats have different movement
        long time = df::getTime();
        float dx = sin((time + randomOffset * 1.0) / 310.1) / 10.0f + sin((time + randomOffset * 2.0) / 500.1) / 10.0f + sin((time + randomOffset * 7.0) / 221.6) / 20.0f + sin((time + randomOffset * 4.0) / 104.2) / 20.0f;
        float dy = sin((time + randomOffset * 1.1) / 580.1) / 10.0f + sin((time + randomOffset * 5.0) / 377.3) / 10.0f + sin((time + randomOffset * 2.0) / 202.7) / 20.0f + sin((time + randomOffset * 3.0) / 82.4) / 20.0f;

        df::ObjectList ol = WM.getSceneGraph().activeObjects();
        df::ObjectListIterator toUpdate(&ol);
        toUpdate.first();
        std::string x = "";
        while(!toUpdate.isDone() && toUpdate.currentObject()) {
            if(toUpdate.currentObject()->getType() == "Player") {
                float dist = (getPosition() - toUpdate.currentObject()->getPosition()).getMagnitude();
                if(dist < 32) {
                    float pdx = getPosition().getX() - toUpdate.currentObject()->getPosition().getX();
                    float pdy = getPosition().getY() - toUpdate.currentObject()->getPosition().getY();

                    df::Vector mov(pdx, pdy);
                    mov.normalize();
                    dx += -mov.getX() / 3.0f;
                    dy += -mov.getY() / 3.0f;
                }
            }
            toUpdate.next();
        }

        setVelocity({dx / 3.0f, dy / 3.0f});
    }

    return 0;
}
