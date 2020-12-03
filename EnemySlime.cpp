#include "EnemySlime.h"

#include "EventStep.h"
#include "WorldManager.h"

EnemySlime::EnemySlime() {
    setType("Slime");
    setSprite("slime");

    hasGravity(true);

    auto b = getBox();
    b = df::Box(df::Vector(b.getCorner().getX() + 0.5f, b.getCorner().getY() + 1.25f), b.getHorizontal() - 1.0f, b.getVertical() - 1.25f);
    setBox(b);

}

int EnemySlime::eventHandler(const df::Event* ev) {

    if(ev->getType() == df::STEP_EVENT) {
        bool ground = isGrounded();
        bool nearPlayer = false;
        float hDir = 0.0f;

        df::ObjectList ol = WM.getSceneGraph().activeObjects();
        df::ObjectListIterator toUpdate(&ol);
        toUpdate.first();
        std::string x = "";
        while(!toUpdate.isDone() && toUpdate.currentObject()) {
            if(toUpdate.currentObject()->getType() == "Player") {
                float dist = (getPosition() - toUpdate.currentObject()->getPosition()).getMagnitude();
                if(dist < 20) {
                    nearPlayer = true;
                }
                float dx = getPosition().getX() - toUpdate.currentObject()->getPosition().getX();
                hDir = dx > 0 ? -0.5f : 0.5f;
            }
            toUpdate.next();
        }

        if(ground && nearPlayer) jumpCooldown--;
        if(!nearPlayer) resetJumpCooldown();

        setVelocity(getVelocity() + df::Vector(0, 0.02f));

        if(ground) {
            setVelocity(getVelocity() * 0.8f);
        }

        if(jumpCooldown <= 0) {
            float jumpStrength = 0.5f;
            jumpStrength += (rand() % 100) / 100.0f * 0.15f;
            setVelocity({getVelocity().getX() + hDir, -jumpStrength});

            resetJumpCooldown();
        }

        if(!ground) {
            getAnimation()->setIndex(0);
            getAnimation()->setSlowdownCount(-1);
        } else {
            if(getAnimation()->getSlowdownCount() == -1) getAnimation()->setSlowdownCount(1);
            if(jumpCooldown < 60) {
                // skip every 2nd and 3rd frame (effective slowdown of 9)
                getAnimation()->setSlowdownCount(getAnimation()->getSlowdownCount() + 1 + getAnimation()->getSlowdownCount() % 2);
            }
            if(nearPlayer) {
                // skip every 3rd frame (effective slowdown of 16)
                getAnimation()->setSlowdownCount(getAnimation()->getSlowdownCount() + getAnimation()->getSlowdownCount() % 2);
            }
        }
    }

    return 0;
}

void EnemySlime::resetJumpCooldown() {
    jumpCooldown = 90 + rand() % 120;
}
