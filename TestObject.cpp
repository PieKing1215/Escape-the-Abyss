/**
	Test Object that is displayed by a sprite and dies after some frames.
	@file TestObject.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "TestObject.h"

// Engine includes
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "EventOut.h"
#include "EventCollision.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "utility.h"

df::TestObject::TestObject() {
	setType("TestObject");
	setSolidness(df::Solidness::HARD);
	kill = 0;
	setSprite("good-spr");
}

df::TestObject::TestObject(df::Vector start_pos, df::Vector velocity) {
	setType("TestObject");
	setSolidness(df::Solidness::HARD);
	setPosition(start_pos);
	setVelocity(velocity);
	kill = 0;
	setSprite("good-spr");
}

int df::TestObject::eventHandler(const df::Event* p_event) {
	// On step event.
	if (p_event->getType() == df::STEP_EVENT) {
		kill++;
		if (kill == (30 * 10)) { // After 10 seconds.
			writeLog("ALERT", "Kill time reached.");
			RM.getSound("game-over")->play();
			GM.setGameOver();
		}
		else if (kill == (30 * 2.5)) { // 2.5 seconds.
			RM.getMusic("start_music")->stop();
		}
		return 1;
	}
	// On out event.
	if (p_event->getType() == df::OUT_EVENT) {
		const df::EventOut* ev_o = dynamic_cast<const df::EventOut*>(p_event);
		std::string text = "";
		if (ev_o->isHard()) {
			text = "Hard";
		}
		else {
			text = "Soft";
		}
		writeLog("ALERT", "%s Out Event.", text.c_str());
		RM.getSound("fire")->play();
		return 1;
	}
	// On collision event.
	if (p_event->getType() == df::COLLISION_EVENT) {
		writeLog("ALERT", "Collision Event.");
		return 1;
	}
	// On keyboard event.
	if (p_event->getType() == df::KEYBOARD_EVENT) {
		writeLog("ALERT", "Keyboard Event.");
		return 1;
	}
	// On mouse event.
	if (p_event->getType() == df::MSE_EVENT) {
		writeLog("ALERT", "Mouse Event.");
		return 1;
	}
	return 0;
}