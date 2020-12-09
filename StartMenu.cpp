/**
	Start Menu screen that displays the title and instructions
	@file StartMenu.cpp
	@author David Mahany (djmahany@wpi.edu)
*/

#include "StartMenu.h"

#include "dragonfly/EventStep.h"
#include "dragonfly/GameManager.h"
#include "dragonfly/WorldManager.h"
#include "dragonfly/ResourceManager.h"
#include "dragonfly/utility.h"

#include "dragonfly/EventKeyboard.h"

StartMenu::StartMenu(Player* pl) {
	setType("StartMenu");
	df::Box v = WM.getView();
	setPosition(df::viewToWorld(df::Vector(v.getHorizontal() / 2, v.getVertical()/2))); // Set location to center
	setSprite("startmenu");
	this->player = pl;

	registerInterest(df::KEYBOARD_EVENT);
}

StartMenu::~StartMenu() {}

int StartMenu::eventHandler(const df::Event* p_e) {

	if(p_e->getType() == df::KEYBOARD_EVENT) {
		df::EventKeyboard* ke = (df::EventKeyboard*)p_e;

		if(ke->getKey() == df::Keyboard::Key::SPACE) {

			player->startFlag();

			return 1;
		}
	}

    return 0;
}

void StartMenu::step(void) {

}

int StartMenu::draw() {
	return df::Object::draw();
}
