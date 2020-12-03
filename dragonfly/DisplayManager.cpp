/**
	Display Manager.
	@file DisplayManager.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "DisplayManager.h"

// Engine includes.
#include "LogManager.h"
#include "utility.h"

df::DisplayManager::DisplayManager() {
	df::Manager::setType("DisplayManager");
	sf::Font* font = &m_font;
	font = NULL;
	// Set up window
	m_p_window = NULL;
	m_window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
	m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;
	m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
	m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;
	m_p_rectangle = NULL;
	m_p_text = NULL;
	m_window_background_color = WINDOW_BACKGROUND_COLOR_DEFAULT;
}

df::DisplayManager::DisplayManager(DisplayManager const&) {
	df::Manager::setType("DisplayManager");
	sf::Font* font = &m_font;
	font = NULL;
	// Set up window
	m_p_window = NULL;
	m_window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
	m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;
	m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
	m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;
	m_p_rectangle = NULL;
	m_p_text = NULL;
	m_window_background_color = WINDOW_BACKGROUND_COLOR_DEFAULT;
}

void df::DisplayManager::operator=(DisplayManager const&) {

}

df::DisplayManager& df::DisplayManager::getInstance() {
	static DisplayManager displayManager;
	return displayManager;
}

int df::DisplayManager::startUp() {
	if (m_p_window) {
		return 0;
	}
	if (!LM.isStarted()) {
		return -1;
	}
	m_p_window = new sf::RenderWindow(sf::VideoMode(getHorizontalPixels(), getVerticalPixels()), "Dragonfly"); // Create window.
	if (!m_p_window) {
		writeLog("", "Failed creating window.");
		return -1;
	}
	m_p_window->setMouseCursorVisible(SHOW_MOUSE); // Hide mouse cursor.
	m_p_window->setVerticalSyncEnabled(VSYNC); // Enable V-Sync.
	// Load font.
	m_font = sf::Font();
	if (!m_font.loadFromFile(FONT_FILE_DEFAULT)) {
		writeLog("ERROR", "Error loading font from %s.", FONT_FILE_DEFAULT.c_str());
		return -1;
	}
	m_window_background_color = sf::Color::Black;
	df::Manager::startUp();
	writeLog("", "Size of window: %dpx x %dpx.", getHorizontalPixels(), getVerticalPixels());
	return 0;
}

void df::DisplayManager::shutDown() {
	writeLog("", "Closing window.");
	m_p_window->close(); // Kill window.
	df::Manager::shutDown();
}

int df::DisplayManager::drawCh(Vector world_pos, char ch, Color color) const {
	if (!m_p_window) {
		writeLog("ALERT", "Cannot draw ch. Window does not exist.");
		return -1;
	}
	df::Vector view_pos = df::worldToView(world_pos); // Convert from text pos to view pos.
	// Create background rectangle for char.
	static sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(charWidth(), charHeight()));
	rectangle.setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);
	rectangle.setPosition(view_pos.getX() - charWidth() / 19, view_pos.getY() + charHeight() / 5);
	m_p_window->draw(rectangle);

	// Create text to display on top of background rectangle.
	static sf::Text text("", m_font);
	text.setString(ch);
	text.setStyle(sf::Text::Bold);
	if (charWidth() < charHeight()) {
		text.setCharacterSize(charWidth() * 2);
	}
	else {
		text.setCharacterSize(charHeight() * 2);
	}
	switch (color) {
	case df::Color::BLACK:
		text.setFillColor(sf::Color::Black);
		break;
	case df::Color::RED:
		text.setFillColor(sf::Color::Red);
		break;
	case df::Color::GREEN:
		text.setFillColor(sf::Color::Green);
		break;
	case df::Color::YELLOW:
		text.setFillColor(sf::Color::Yellow);
		break;
	case df::Color::BLUE:
		text.setFillColor(sf::Color::Blue);
		break;
	case df::Color::MAGENTA:
		text.setFillColor(sf::Color::Magenta);
		break;
	case df::Color::CYAN:
		text.setFillColor(sf::Color::Cyan);
		break;
	case df::Color::WHITE:
		text.setFillColor(sf::Color::White);
	}
	df::Vector pixel_pos = spacesToPixels(view_pos);
	text.setPosition(pixel_pos.getX(), pixel_pos.getY());
	m_p_window->draw(text);
	return 0;
}

int df::DisplayManager::swapBuffers() {
	if (!m_p_window) {
		writeLog("ALERT", "Cannot swap buffers. Window does not exist.");
		return -1;
	}

	m_p_window->display(); // Display buffer
	m_p_window->clear(m_window_background_color); // Clear buffer with all black
	return 0;
}

int df::DisplayManager::drawString(Vector pos, std::string str, Justification just, Color color) const {
	if (!m_p_window) {
		writeLog("ALERT", "Cannot draw ch. Window does not exist.");
		return -1;
	}
	df::Vector start_pos = pos;
	// Set up start_pos to account for justification.
	switch (just) {
	case df::Justification::CENTER_JUSTIFIED:
		start_pos.setX(pos.getX() - str.size() / 2);
		break;
	case df::Justification::RIGHT_JUSTIFIED:
		start_pos.setX(pos.getX() - str.size());
		break;
	}

	// Loop through string and display each character.
	for (int i = 0; i < str.size(); i++) {
		df::Vector tmp_pos(start_pos.getX() + i, start_pos.getY());
		if (drawCh(tmp_pos, str[i], color) == -1) {
			writeLog("ERROR", "ERROR", "Error drawing string.");
			return -1;
		}
	}
	return 0;
}

int df::DisplayManager::getHorizontal() const {
	return m_window_horizontal_chars;
}

int df::DisplayManager::getVertical() const {
	return m_window_vertical_chars;
}

int df::DisplayManager::getHorizontalPixels() const {
	return m_window_horizontal_pixels;
}

int df::DisplayManager::getVerticalPixels() const {
	return m_window_vertical_pixels;
}

sf::RenderWindow* df::DisplayManager::getWindow() const {
	return m_p_window;
}

bool df::DisplayManager::setBackgroundColor(int new_color) {
	if (!m_p_window) {
		writeLog("ALERT", "Cannot draw ch. Window does not exist.");
		return false;
	}
	switch (new_color) {
	case (static_cast<int>(df::Color::BLACK)):
		m_window_background_color = sf::Color::Black;
		break;
	case (static_cast<int>(df::Color::RED)):
		m_window_background_color = sf::Color::Red;
		break;
	case (static_cast<int>(df::Color::GREEN)):
		m_window_background_color = sf::Color::Green;
		break;
	case (static_cast<int>(df::Color::YELLOW)):
		m_window_background_color = sf::Color::Yellow;
		break;
	case (static_cast<int>(df::Color::BLUE)):
		m_window_background_color = sf::Color::Blue;
		break;
	case (static_cast<int>(df::Color::MAGENTA)):
		m_window_background_color = sf::Color::Magenta;
		break;
	case (static_cast<int>(df::Color::CYAN)):
		m_window_background_color = sf::Color::Cyan;
		break;
	case (static_cast<int>(df::Color::WHITE)):
		m_window_background_color = sf::Color::White;
	}
	return true;
}

float df::charHeight() {
	return ((float)DM.getVerticalPixels()) / ((float)DM.getVertical());
}

float df::charWidth() {
	return ((float)DM.getHorizontalPixels()) / ((float)DM.getHorizontal());
}

df::Vector df::spacesToPixels(Vector spaces) {
	df::Vector v(df::charWidth(), df::charHeight());
	return spaces * v;
}

df::Vector df::pixelsToSpaces(Vector pixels) {
	df::Vector v(df::charWidth(), df::charHeight());
	return pixels / v;
}