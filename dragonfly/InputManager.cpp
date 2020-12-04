/**
	Input manager.
	@file InputManager.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "InputManager.h"

// Engine includes
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "WorldManager.h"

df::InputManager::InputManager() {
	setType("InputManager");
}

df::InputManager::InputManager(InputManager const&) {
	setType("InputManager");
}

void df::InputManager::operator=(InputManager const&) {

}

df::InputManager& df::InputManager::getInstance() {
	static InputManager displayManager;
	return displayManager;
}

int df::InputManager::startUp() {
	if (!LM.isStarted()) {
		return -1;
	}
	if (!WM.isStarted()) {
		writeLog("ERROR", "Error starting InputManager. WorldManager not started yet.");
		return -1;
	}
	if (!DM.isStarted()) {
		writeLog("ERROR", "Error starting InputManager. DisplayManager not started yet.");
		return -1;
	}
	DM.getWindow()->setKeyRepeatEnabled(false); // Disable repeat event dispatches.
	df::Manager::startUp();
	return 0;
}

void df::InputManager::shutDown() {
	DM.getWindow()->setKeyRepeatEnabled(true); // Reenable repeat event dispatches.
	df::Manager::shutDown();
}

void df::InputManager::getInput() {
	// Map of SFML keys to Dragonfly keys
	sf::Keyboard::Key sfKeys[] = {
		sf::Keyboard::Key::Space,
		sf::Keyboard::Key::Return,
		sf::Keyboard::Key::Escape,
		sf::Keyboard::Key::Tab,
		sf::Keyboard::Key::Left,
		sf::Keyboard::Key::Right,
		sf::Keyboard::Key::Up,
		sf::Keyboard::Key::Down,
		sf::Keyboard::Key::Pause,
		sf::Keyboard::Key::Subtract,
		sf::Keyboard::Key::Add,
		sf::Keyboard::Key::Tilde,
		sf::Keyboard::Key::Period,
		sf::Keyboard::Key::Comma,
		sf::Keyboard::Key::Slash,
		sf::Keyboard::Key::Equal,
		sf::Keyboard::Key::BackSlash,
		sf::Keyboard::Key::Multiply,
		sf::Keyboard::Key::Quote,
		sf::Keyboard::Key::SemiColon,
		sf::Keyboard::Key::LControl,
		sf::Keyboard::Key::RControl,
		sf::Keyboard::Key::LShift,
		sf::Keyboard::Key::RShift,
		sf::Keyboard::Key::F1,
		sf::Keyboard::Key::F2,
		sf::Keyboard::Key::F3,
		sf::Keyboard::Key::F4,
		sf::Keyboard::Key::F5,
		sf::Keyboard::Key::F6,
		sf::Keyboard::Key::F7,
		sf::Keyboard::Key::F8,
		sf::Keyboard::Key::F9,
		sf::Keyboard::Key::F10,
		sf::Keyboard::Key::F11,
		sf::Keyboard::Key::F12,
		sf::Keyboard::Key::A,
		sf::Keyboard::Key::B,
		sf::Keyboard::Key::C,
		sf::Keyboard::Key::D,
		sf::Keyboard::Key::E,
		sf::Keyboard::Key::F,
		sf::Keyboard::Key::G,
		sf::Keyboard::Key::H,
		sf::Keyboard::Key::I,
		sf::Keyboard::Key::J,
		sf::Keyboard::Key::K,
		sf::Keyboard::Key::L,
		sf::Keyboard::Key::M,
		sf::Keyboard::Key::N,
		sf::Keyboard::Key::O,
		sf::Keyboard::Key::P,
		sf::Keyboard::Key::Q,
		sf::Keyboard::Key::R,
		sf::Keyboard::Key::S,
		sf::Keyboard::Key::T,
		sf::Keyboard::Key::U,
		sf::Keyboard::Key::V,
		sf::Keyboard::Key::W,
		sf::Keyboard::Key::X,
		sf::Keyboard::Key::Y,
		sf::Keyboard::Key::Z,
		sf::Keyboard::Key::Num1,
		sf::Keyboard::Key::Num2,
		sf::Keyboard::Key::Num3,
		sf::Keyboard::Key::Num4,
		sf::Keyboard::Key::Num5,
		sf::Keyboard::Key::Num6,
		sf::Keyboard::Key::Num7,
		sf::Keyboard::Key::Num8,
		sf::Keyboard::Key::Num9,
		sf::Keyboard::Key::Num0,
		sf::Keyboard::Key::BackSpace
	};
	df::Keyboard::Key dfKeys[] = {
		df::Keyboard::Key::SPACE,
		df::Keyboard::Key::RETURN,
		df::Keyboard::Key::ESCAPE,
		df::Keyboard::Key::TAB,
		df::Keyboard::Key::LEFTARROW,
		df::Keyboard::Key::RIGHTARROW,
		df::Keyboard::Key::UPARROW,
		df::Keyboard::Key::DOWNARROW,
		df::Keyboard::Key::PAUSE,
		df::Keyboard::Key::MINUS,
		df::Keyboard::Key::PLUS,
		df::Keyboard::Key::TILDE,
		df::Keyboard::Key::PERIOD,
		df::Keyboard::Key::COMMA,
		df::Keyboard::Key::SLASH,
		df::Keyboard::Key::EQUAL,
		df::Keyboard::Key::BACKSLASH,
		df::Keyboard::Key::MULTIPLY,
		df::Keyboard::Key::QUOTE,
		df::Keyboard::Key::SEMICOLON,
		df::Keyboard::Key::LEFTCONTROL,
		df::Keyboard::Key::RIGHTCONTROL,
		df::Keyboard::Key::LEFTSHIFT,
		df::Keyboard::Key::RIGHTSHIFT,
		df::Keyboard::Key::F1,
		df::Keyboard::Key::F2,
		df::Keyboard::Key::F3,
		df::Keyboard::Key::F4,
		df::Keyboard::Key::F5,
		df::Keyboard::Key::F6,
		df::Keyboard::Key::F7,
		df::Keyboard::Key::F8,
		df::Keyboard::Key::F9,
		df::Keyboard::Key::F10,
		df::Keyboard::Key::F11,
		df::Keyboard::Key::F12,
		df::Keyboard::Key::A,
		df::Keyboard::Key::B,
		df::Keyboard::Key::C,
		df::Keyboard::Key::D,
		df::Keyboard::Key::E,
		df::Keyboard::Key::F,
		df::Keyboard::Key::G,
		df::Keyboard::Key::H,
		df::Keyboard::Key::I,
		df::Keyboard::Key::J,
		df::Keyboard::Key::K,
		df::Keyboard::Key::L,
		df::Keyboard::Key::M,
		df::Keyboard::Key::N,
		df::Keyboard::Key::O,
		df::Keyboard::Key::P,
		df::Keyboard::Key::Q,
		df::Keyboard::Key::R,
		df::Keyboard::Key::S,
		df::Keyboard::Key::T,
		df::Keyboard::Key::U,
		df::Keyboard::Key::V,
		df::Keyboard::Key::W,
		df::Keyboard::Key::X,
		df::Keyboard::Key::Y,
		df::Keyboard::Key::Z,
		df::Keyboard::Key::NUM1,
		df::Keyboard::Key::NUM2,
		df::Keyboard::Key::NUM3,
		df::Keyboard::Key::NUM4,
		df::Keyboard::Key::NUM5,
		df::Keyboard::Key::NUM6,
		df::Keyboard::Key::NUM7,
		df::Keyboard::Key::NUM8,
		df::Keyboard::Key::NUM9,
		df::Keyboard::Key::NUM0,
		df::Keyboard::Key::BACKSPACE
	};

	sf::Event event;
	while (DM.getWindow()->pollEvent(event)) { // Poll for input events.
		// Key press event.
		if (event.type == sf::Event::KeyPressed) {
			df::EventKeyboard eventKeyboard;
			eventKeyboard.setKeyboardAction(df::EventKeyboardAction::KEY_PRESSED);

			for(int i = 0; i < sizeof(dfKeys) / sizeof(dfKeys[0]); i++) {
				if(sfKeys[i] == event.key.code) {
					eventKeyboard.setKey(dfKeys[i]);
				}
			}

			WM.onEvent(&eventKeyboard);
		}
		// Key release event.
		if (event.type == sf::Event::KeyReleased) {
			df::EventKeyboard eventKeyboard;
			eventKeyboard.setKeyboardAction(df::EventKeyboardAction::KEY_RELEASED);

			for(int i = 0; i < sizeof(dfKeys) / sizeof(dfKeys[0]); i++) {
				if(sfKeys[i] == event.key.code) {
					eventKeyboard.setKey(dfKeys[i]);
				}
			}

			WM.onEvent(&eventKeyboard);
		}
		// Mouse move event.
		if (event.type == sf::Event::MouseMoved) {
			df::EventMouse eventMouse;
			df::Vector v((float)event.mouseMove.x * DM.getHorizontalPixels(), (float)event.mouseMove.y * DM.getVerticalPixels());
			eventMouse.setMouseAction(df::EventMouseAction::MOVED);
			eventMouse.setMousePosition(v);
			WM.onEvent(&eventMouse);
		}
		// Mouse button press.
		if (event.type == sf::Event::MouseButtonPressed) {
			df::EventMouse eventMouse;
			eventMouse.setMouseAction(df::EventMouseAction::CLICKED);
			switch (event.mouseButton.button) {
			case sf::Mouse::Left:
				eventMouse.setMouseButton(df::Mouse::Button::LEFT);
				break;
			case sf::Mouse::Middle:
				eventMouse.setMouseButton(df::Mouse::Button::MIDDLE);
				break;
			case sf::Mouse::Right:
				eventMouse.setMouseButton(df::Mouse::Button::RIGHT);
				break;
			}
			eventMouse.setMousePosition({(float)event.mouseButton.x, (float)event.mouseButton.y});
			WM.onEvent(&eventMouse);
		}
	}
	

	// Dispatch events for currently pressed keys.
	for (int i = 0; i < sizeof(dfKeys) / sizeof(dfKeys[0]); i++) {
		if (sf::Keyboard::isKeyPressed(sfKeys[i])) {
			EventKeyboard eventKeyboard;
			eventKeyboard.setKeyboardAction(df::EventKeyboardAction::KEY_DOWN);
			eventKeyboard.setKey(dfKeys[i]);
			WM.onEvent(&eventKeyboard);
		}
	}
	// Map of SFML mouse buttons to Dragonfly mouse buttons
	sf::Mouse::Button sfButtons[] = {
		sf::Mouse::Button::Left,
		sf::Mouse::Button::Middle,
		sf::Mouse::Button::Right
	};
	df::Mouse::Button dfButtons[] = {
		df::Mouse::Button::LEFT,
		df::Mouse::Button::MIDDLE,
		df::Mouse::Button::RIGHT
	};

	// Dispatch events for currently pressed mouse buttons.
	for (int i = 0; i < sizeof(dfButtons) / sizeof(dfButtons[0]); i++) {
		if (sf::Mouse::isButtonPressed(sfButtons[i])) {
			df::EventMouse eventMouse;
			eventMouse.setMouseAction(df::EventMouseAction::PRESSED);
			eventMouse.setMouseButton(dfButtons[i]);
			WM.onEvent(&eventMouse);
		}
	}
}

bool df::InputManager::isKeyDown(df::Keyboard::Key key) {
	sf::Keyboard::Key sfKeys[] = {
		sf::Keyboard::Key::Space,
		sf::Keyboard::Key::Return,
		sf::Keyboard::Key::Escape,
		sf::Keyboard::Key::Tab,
		sf::Keyboard::Key::Left,
		sf::Keyboard::Key::Right,
		sf::Keyboard::Key::Up,
		sf::Keyboard::Key::Down,
		sf::Keyboard::Key::Pause,
		sf::Keyboard::Key::Subtract,
		sf::Keyboard::Key::Add,
		sf::Keyboard::Key::Tilde,
		sf::Keyboard::Key::Period,
		sf::Keyboard::Key::Comma,
		sf::Keyboard::Key::Slash,
		sf::Keyboard::Key::Equal,
		sf::Keyboard::Key::BackSlash,
		sf::Keyboard::Key::Multiply,
		sf::Keyboard::Key::Quote,
		sf::Keyboard::Key::SemiColon,
		sf::Keyboard::Key::LControl,
		sf::Keyboard::Key::RControl,
		sf::Keyboard::Key::LShift,
		sf::Keyboard::Key::RShift,
		sf::Keyboard::Key::F1,
		sf::Keyboard::Key::F2,
		sf::Keyboard::Key::F3,
		sf::Keyboard::Key::F4,
		sf::Keyboard::Key::F5,
		sf::Keyboard::Key::F6,
		sf::Keyboard::Key::F7,
		sf::Keyboard::Key::F8,
		sf::Keyboard::Key::F9,
		sf::Keyboard::Key::F10,
		sf::Keyboard::Key::F11,
		sf::Keyboard::Key::F12,
		sf::Keyboard::Key::A,
		sf::Keyboard::Key::B,
		sf::Keyboard::Key::C,
		sf::Keyboard::Key::D,
		sf::Keyboard::Key::E,
		sf::Keyboard::Key::F,
		sf::Keyboard::Key::G,
		sf::Keyboard::Key::H,
		sf::Keyboard::Key::I,
		sf::Keyboard::Key::J,
		sf::Keyboard::Key::K,
		sf::Keyboard::Key::L,
		sf::Keyboard::Key::M,
		sf::Keyboard::Key::N,
		sf::Keyboard::Key::O,
		sf::Keyboard::Key::P,
		sf::Keyboard::Key::Q,
		sf::Keyboard::Key::R,
		sf::Keyboard::Key::S,
		sf::Keyboard::Key::T,
		sf::Keyboard::Key::U,
		sf::Keyboard::Key::V,
		sf::Keyboard::Key::W,
		sf::Keyboard::Key::X,
		sf::Keyboard::Key::Y,
		sf::Keyboard::Key::Z,
		sf::Keyboard::Key::Num1,
		sf::Keyboard::Key::Num2,
		sf::Keyboard::Key::Num3,
		sf::Keyboard::Key::Num4,
		sf::Keyboard::Key::Num5,
		sf::Keyboard::Key::Num6,
		sf::Keyboard::Key::Num7,
		sf::Keyboard::Key::Num8,
		sf::Keyboard::Key::Num9,
		sf::Keyboard::Key::Num0,
		sf::Keyboard::Key::BackSpace
	};
	df::Keyboard::Key dfKeys[] = {
		df::Keyboard::Key::SPACE,
		df::Keyboard::Key::RETURN,
		df::Keyboard::Key::ESCAPE,
		df::Keyboard::Key::TAB,
		df::Keyboard::Key::LEFTARROW,
		df::Keyboard::Key::RIGHTARROW,
		df::Keyboard::Key::UPARROW,
		df::Keyboard::Key::DOWNARROW,
		df::Keyboard::Key::PAUSE,
		df::Keyboard::Key::MINUS,
		df::Keyboard::Key::PLUS,
		df::Keyboard::Key::TILDE,
		df::Keyboard::Key::PERIOD,
		df::Keyboard::Key::COMMA,
		df::Keyboard::Key::SLASH,
		df::Keyboard::Key::EQUAL,
		df::Keyboard::Key::BACKSLASH,
		df::Keyboard::Key::MULTIPLY,
		df::Keyboard::Key::QUOTE,
		df::Keyboard::Key::SEMICOLON,
		df::Keyboard::Key::LEFTCONTROL,
		df::Keyboard::Key::RIGHTCONTROL,
		df::Keyboard::Key::LEFTSHIFT,
		df::Keyboard::Key::RIGHTSHIFT,
		df::Keyboard::Key::F1,
		df::Keyboard::Key::F2,
		df::Keyboard::Key::F3,
		df::Keyboard::Key::F4,
		df::Keyboard::Key::F5,
		df::Keyboard::Key::F6,
		df::Keyboard::Key::F7,
		df::Keyboard::Key::F8,
		df::Keyboard::Key::F9,
		df::Keyboard::Key::F10,
		df::Keyboard::Key::F11,
		df::Keyboard::Key::F12,
		df::Keyboard::Key::A,
		df::Keyboard::Key::B,
		df::Keyboard::Key::C,
		df::Keyboard::Key::D,
		df::Keyboard::Key::E,
		df::Keyboard::Key::F,
		df::Keyboard::Key::G,
		df::Keyboard::Key::H,
		df::Keyboard::Key::I,
		df::Keyboard::Key::J,
		df::Keyboard::Key::K,
		df::Keyboard::Key::L,
		df::Keyboard::Key::M,
		df::Keyboard::Key::N,
		df::Keyboard::Key::O,
		df::Keyboard::Key::P,
		df::Keyboard::Key::Q,
		df::Keyboard::Key::R,
		df::Keyboard::Key::S,
		df::Keyboard::Key::T,
		df::Keyboard::Key::U,
		df::Keyboard::Key::V,
		df::Keyboard::Key::W,
		df::Keyboard::Key::X,
		df::Keyboard::Key::Y,
		df::Keyboard::Key::Z,
		df::Keyboard::Key::NUM1,
		df::Keyboard::Key::NUM2,
		df::Keyboard::Key::NUM3,
		df::Keyboard::Key::NUM4,
		df::Keyboard::Key::NUM5,
		df::Keyboard::Key::NUM6,
		df::Keyboard::Key::NUM7,
		df::Keyboard::Key::NUM8,
		df::Keyboard::Key::NUM9,
		df::Keyboard::Key::NUM0,
		df::Keyboard::Key::BACKSPACE
	};

	for(int i = 0; i < sizeof(dfKeys) / sizeof(dfKeys[0]); i++) {
		if(dfKeys[i] == key) {
			return sf::Keyboard::isKeyPressed(sfKeys[i]);
		}
	}

	return false;
}

bool df::InputManager::isValid(std::string event_name) const {
	return (event_name == df::KEYBOARD_EVENT || event_name == df::MSE_EVENT);
}