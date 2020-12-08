/**
	The player.
	@file Player.cpp
	@author David Mahany (djmahany@wpi.edu)
*/

#include "Player.h"

// Engine includes.
#include "dragonfly/GameManager.h"
#include "dragonfly/ResourceManager.h"
#include "dragonfly/InputManager.h"
#include "dragonfly/WorldManager.h"
#include "dragonfly/DisplayManager.h"

#include "dragonfly/EventStep.h"
#include "dragonfly/EventCollision.h"
#include "dragonfly/EventKeyboard.h"
#include "dragonfly/EventMouse.h"

#include "dragonfly/utility.h"

// Game includes.
#include "FloorManager.h"
#include "EnemyMaster.h"
#include "GameOver.h"

static int lives = 1;

Player::Player() {
	setType("Player");

	// TODO: we shouldn't need to set boxes manually. setSprite does it for us
	auto b = getBox();
	b = df::Box(df::Vector(b.getCorner().getX() + 0.25f, b.getCorner().getY() + 0.5f), b.getHorizontal() - 0.5f, b.getVertical() - 0.5f);
	//setBox(b);

	// enable gravity
	hasGravity(true);

	// set initial health (keep track of max health too in case we want a health bar or something later)
	health = maxHealth = 4.0f;

	//registerInterest(df::STEP_EVENT);
	registerInterest(df::COLLISION_EVENT);
	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::MSE_EVENT);

	setSprite("player-bounds");
}

int Player::eventHandler(const df::Event* p_e) {

	if(p_e->getType() == df::STEP_EVENT) {

		// tick cooldowns
		if(attackCooldown > 0) attackCooldown--;
		if(invulnerability > 0) invulnerability--;

		// cutscenes
		if (playEndAnim) {
			if (!endAnimFire) {
				endAnimFire = true;
				WM.setViewFollowing(NULL);
			}
		}
		else if (playStartAnim) {
			startTickCounter++;
			if (startTickCounter == 30 * 7.5) {
				WM.setViewFollowing(this);
				WM.setViewSlack(df::Vector(0.25, 0.25));
			} else if (startTickCounter > 30 * 10 && startTickCounter < 30 * 12) {
				jump();
				startAnimFire = true;
			}
			else if (startAnimFire && isGrounded()) {
				playStartAnim = false;
			}
		}

		// update movement
		tickMovement();
		return 1;
	} else if(p_e->getType() == df::KEYBOARD_EVENT) {
		df::EventKeyboard* ke = (df::EventKeyboard*)p_e;

		if (ke->getKey() == df::Keyboard::Key::SPACE) {
			if (ke->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED) {
				// space pressed, start a jump
				jump();
				return 1;
			}
			else if (ke->getKeyboardAction() == df::EventKeyboardAction::KEY_RELEASED) {
				// space released, end the jump
				endJump();
				return 1;
			}
		}

		if (ke->getKey() == df::Keyboard::Key::Q) {
			if (ke->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED) {
				// Q pressed, quit the game
				GM.setGameOver();
				return 1;
			}
		}
		

	} else if(p_e->getType() == df::MSE_EVENT) {
		df::EventMouse* me = (df::EventMouse*)p_e;

		// on left mouse click and attack cooldown is ready
		if(attackCooldown == 0 && me->getMouseAction() == df::EventMouseAction::CLICKED && me->getMouseButton() == df::Mouse::Button::LEFT) {
			attackCooldown = 40;

			// calculate if the click was to the left or right of the player
			df::Vector ppos = df::spacesToPixels(df::worldToView(getPosition()));
			auto dpos = me->getMousePosition() - ppos;
			bool left = dpos.getX() < 0;

			// spawn attack
			PlayerAttack* atk = new PlayerAttack(this, left);
			atk->setPosition(this->getPosition() + df::Vector(0, -0.5f));
		}

	} else if(p_e->getType() == df::COLLISION_EVENT) {
		df::EventCollision* ce = (df::EventCollision*)p_e;

		// take damage if contacted enemy
		if(dynamic_cast<EnemyMaster*>(ce->getObject1())) {
			damage(1.0f, ce->getObject1()->getPosition());
		}else if(dynamic_cast<EnemyMaster*>(ce->getObject2())) {
			damage(1.0f, ce->getObject2()->getPosition());
        }
	}

	return 0;
}

int Player::draw() {

	// since we the player's legs and body animate separately, we need to use a combination of multiple sprites
	// the Object's "real" sprite (using setSprite) is "player-bounds" which is a 2x3, completely empty sprite only used for collisions

	// flash during invulnerability
	bool flash = invulnerability % 6 >= 5;

	if(!flash) RM.getSprite("player-idle-body")->draw(0, this->getPosition() + df::Vector(-1, -1));

	// decide which frame for the legs
	// 0 = "/ \"
	// 1 = " | "
	int legFrame = walkCycle > 0.5f ? 1 : 0;

	if(!isGrounded()) {
		// always use "/ \" in the air
		legFrame = 0;
	} else {
		if(abs(getVelocity().getX()) < 0.1) {
			// always use " | " if on the ground and standing still
			legFrame = 1;
			walkCycle = 0;
		} else {
			// cycle between frames based on x velocity
			walkCycle += abs(getVelocity().getX()) / 3.0f;
			while(walkCycle > 1.0f) walkCycle -= 1.0f;
		}
	}

	if(!flash) RM.getSprite("player-walk")->draw(legFrame, this->getPosition() + df::Vector(-1, 0.2f + 1));

	return Object::draw();
}

void Player::tickMovement() {
	float vx = getVelocity().getX();
	float vy = getVelocity().getY();

	// state of the relevant inputs
	bool aDown = IM.isKeyDown(df::Keyboard::Key::A);
	bool dDown = IM.isKeyDown(df::Keyboard::Key::D);

	// For cutscenes
	if (playStartAnim) {
		if (startTickCounter < 30 * 7.5 || (startTickCounter > 30 * 9.8 && startTickCounter < 30 * 11.8) || (startTickCounter > 30 * 12 && startTickCounter % 120 >= 60)) {
			aDown = true;
			dDown = false;
		}
		else if (startTickCounter > 30 * 12) {
			aDown = false;
			dDown = true;
		}
	} else if (playEndAnim) {
		aDown = false;
		dDown = true;
	}

	bool grounded = isGrounded();

	// -X if holding A, +X if holding D
	float xMove = (aDown ? -0.02f : 0.0f) + (dDown ? 0.02f : 0.0f);

	// when not pressing left or right
	if(!aDown && !dDown) {
		// slow down 
		float factor = grounded ? 0.85f : 0.98f;
		vx *= factor;
	}

	// when pressing the opposite direction as your current velocity
	if((vx > 0 && xMove < 0) || (vx < 0 && xMove > 0)) {
		// give a boost to movement power (helps when "turning around")
		float factor = grounded ? 3.0f : 2.0f;
		xMove *= factor;
	}

	// when on the ground and pressing the same direction as your current velocity
	if((vx < 0 && xMove < 0) || (vx > 0 && xMove > 0)) {
		// help push towards max speed
		float maxSpeed = 0.5f;
		float thru = maxSpeed - abs(vx);

		int sign = (vx < 0 ? -1 : 1);
		float factor = grounded ? 20.0f : 40.0f;
		xMove += thru / factor * sign;
	}

	// add the movement velocity
	vx += xMove;

	// dampening
	vx *= 0.98f;
	vy *= 0.99f;

	setVelocity({vx, vy});
}

void Player::jump() {
	// start jump
	if(isGrounded()) setVelocity({getVelocity().getX(), -0.6f});
}

void Player::endJump() {
	// allows "cancelling" so you can do short jumps by releasing the key early and high jumps by holding the key until the max height
	if(getVelocity().getY() < 0) {
		setVelocity({getVelocity().getX(), getVelocity().getY() * 0.5f});
	}
}

void Player::damage(float damage, df::Vector source) {
	// no damage if invulnerable
	if(invulnerability > 0) return;

	health -= damage;
	if(health <= 0) {
		health = 0;
		die();
	}
	invulnerability = 60;

	// randomish knockback, pushes away from the source given as an argument
	float knockStrength = 0.4f + (rand() % 100) / 100.0f * 0.15f;
	int knockDir = source.getX() > getPosition().getX() ? -1 : 1;
	setVelocity({getVelocity().getX() + knockStrength * knockDir, getVelocity().getY() - 0.35f});
}

void Player::die() {

	setVelocity({0, 0});
	WM.setViewFollowing(NULL);
	WM.markForDelete(this);

    lives--;
    if (lives > 0) {
        FM.respawn();
    }
    else {
        new GameOver;
    }
}

void Player::endAnim() {
	playEndAnim = true;
}

PlayerAttack::PlayerAttack(Player* pl, bool left) {
	setSolidness(df::Solidness::SOFT);
	setSprite(left ? "player-attack-l" : "player-attack-r");

	this->player = pl;
	this->left = left;
	this->lifetime = 20;

	// set box for frame 1
	auto b = getBox();
	if(left) {
		b = df::Box(df::Vector(-2.0f, -1.25f), 2.0f, 2.25f);
	} else {
		b = df::Box(df::Vector(0.0f, -1.25f), 2.0f, 2.25f);
	}
	setBox(b);
	
	registerInterest(df::COLLISION_EVENT);

}

int PlayerAttack::eventHandler(const df::Event* p_e) {

	if(p_e->getType() == df::STEP_EVENT) {

		setPosition(player->getPosition() + df::Vector(0, -0.5f));

		this->lifetime--;
		if(lifetime == 12) {
			// set box for frame 2
			auto b = getBox();
			if(left) {
				b = df::Box(df::Vector(-3.25f, -0.25f), 3.25f, 1.75f);
			} else {
				b = df::Box(df::Vector(0.0f, -0.25f), 3.25f, 1.75f);
			}
			setBox(b);
		}

		if(lifetime == 6) {
			// set box for frame 3
			auto b = getBox();
			if(left) {
				b = df::Box(df::Vector(-2.25f, -0.25f), 2.25f, 2.0f);
			} else {
				b = df::Box(df::Vector(0.0f, -0.25f), 2.25f, 2.0f);
			}
			setBox(b);
		}
		if(this->lifetime <= 0) WM.markForDelete(this);
	} else if(p_e->getType() == df::COLLISION_EVENT) {
		df::EventCollision* ce = (df::EventCollision*)p_e;

		// delete enemy on contact
		if(dynamic_cast<EnemyMaster*>(ce->getObject1())) {
			WM.markForDelete(ce->getObject1());
		} else if(dynamic_cast<EnemyMaster*>(ce->getObject2())) {
			WM.markForDelete(ce->getObject2());
		}
	}

	return 0;
}

int PlayerAttack::draw() {
	return Object::draw();
}