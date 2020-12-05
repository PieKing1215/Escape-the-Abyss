/**
	Resource Manager.
	@file ResourceManager.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "ResourceManager.h"

// Engine includes.
#include "LogManager.h"

// System includes.
#include <iostream>
#include <fstream>

df::ResourceManager::ResourceManager() {
	setType("ResourceManager");
	p_sprite[0] = NULL;
	m_sprite_count = 0;
	m_sound;
	m_sound_count = 0;
	m_music;
	m_music_count = 0;
}

df::ResourceManager::ResourceManager(ResourceManager const&) {
	setType("ResourceManager");
	p_sprite[0] = NULL;
	m_sprite_count = 0;
	m_sound;
	m_sound_count = 0;
	m_music;
	m_music_count = 0;
}

void df::ResourceManager::operator=(ResourceManager const&) {

}

df::ResourceManager& df::ResourceManager::getInstance() {
	static ResourceManager resourceManager;
	return resourceManager;
}

int df::ResourceManager::startUp() {
	if (!LM.isStarted()) {
		return -1;
	}
	m_sprite_count = 0;
	m_sound_count = 0;
	m_music_count = 0;
	df::Manager::startUp();
	return 0;
}

void df::ResourceManager::shutDown() {
	for (int i = 0; i < m_sprite_count; i++) {
		unloadSprite(p_sprite[i]->getLabel());
	}
	for (int i = 0; i < m_sound_count; i++) {
		unloadSound(m_sound[i].getLabel());
	}
	for (int i = 0; i < m_music_count; i++) {
		unloadMusic(m_music[i].getLabel());
	}
	df::Manager::shutDown();
}

int df::ResourceManager::loadSprite(std::string filename, std::string label) {
	writeLog("", "Loading sprite '%s'.", label.c_str());
	if (m_sprite_count >= MAX_SPRITES) {
		writeLog("ERROR", "Unable to load sprite '%s'. Sprite array full.", label.c_str());
		return -1;
	}
	for (int i = 0; i < m_sprite_count; i++) {
		if (label == p_sprite[i]->getLabel()) {
			writeLog("ERROR", "Cannot load sprite with label '%s'. '%s' already loaded.", label.c_str(), label.c_str());
			return -1;
		}
	}
	writeLog("", "Loading file '%s'.", filename.c_str());
	std::ifstream file(filename.c_str());
	if (!file.good()) {
		writeLog("ERROR", "Error opening '%s' sprite from file '%s'.", label.c_str(), filename.c_str());
		writeLog("ALERT", "Sprite '%s' not loaded.", label.c_str());
		file.close();
		return -1;
	}
	std::vector<std::string> data = readData(&file, HEADER_TOKEN);
	int x = matchLineInt(&data, "frames");
	if (x == -1) {
		writeLog("ERROR", "Error loading %s sprite: %s not declared in %s", label.c_str(), "frames", HEADER_TOKEN);
		writeLog("ALERT", "Sprite '%s' not loaded.", label.c_str());
		file.close();
		return -1;
	}
	df::Sprite* sprite = new df::Sprite(x);
	x = matchLineInt(&data, "width");
	if (x == -1) {
		writeLog("ERROR", "Error loading %s sprite: %s not declared in %s", label.c_str(), "width", HEADER_TOKEN);
		writeLog("ALERT", "Sprite '%s' not loaded.", label.c_str());
		delete sprite;
		file.close();
		return -1;
	}
	sprite->setWidth(x);
	x = matchLineInt(&data, "height");
	if (x == -1) {
		writeLog("ERROR", "Error loading %s sprite: %s not declared in %s", label.c_str(), "height", HEADER_TOKEN);
		writeLog("ALERT", "Sprite '%s' not loaded.", label.c_str());
		delete sprite;
		file.close();
		return -1;
	}
	sprite->setHeight(x);
	std::string y = matchLineStr(&data, "color");
	if (y != "") {
		if (y == "black") {
			sprite->setColor(df::Color::BLACK);
		}
		else if (y == "red") {
			sprite->setColor(df::Color::RED);
		}
		else if (y == "green") {
			sprite->setColor(df::Color::GREEN);
		}
		else if (y == "yellow") {
			sprite->setColor(df::Color::YELLOW);
		}
		else if (y == "blue") {
			sprite->setColor(df::Color::BLUE);
		}
		else if (y == "magenta") {
			sprite->setColor(df::Color::MAGENTA);
		}
		else if (y == "cyan") {
			sprite->setColor(df::Color::CYAN);
		}
		else if (y == "white") {
			sprite->setColor(df::Color::WHITE);
		}
		else if (y == "custom") {
			sprite->setColor(df::Color::CUSTOM);
		}
		else {
			sprite->setColor(df::COLOR_DEFAULT);
		}
	}
	y = matchLineStr(&data, "transparent");
	if (y.length() > 0) {
		sprite->setTransparent(y[0]);
	}
	x = matchLineInt(&data, "slowdown");
	if (x != -1) {
		sprite->setSlowdown(x);
	}
	data = readData(&file, BODY_TOKEN);
	for (int i = 0; i < sprite->getFrameCount(); i++) {
		df::Frame frame = matchFrame(&data, sprite->getWidth(), sprite->getHeight());
		if (frame.getWidth() == 0 && frame.getHeight() == 0 && frame.getString() == "" && frame.getTransparency() == 0) { // Is an empty frame
			writeLog("ERROR", "Error loading %s sprite: %d frame not declared properly in %s", label.c_str(), i, BODY_TOKEN);
			writeLog("ALERT", "Sprite '%s' not loaded.", label.c_str());
			delete sprite;
			file.close();
			return -1;
		}
		sprite->addFrame(frame);
	}
	// Not using data in footer.
	// data = readData(&file, FOOTER_TOKEN);
	file.close();
	sprite->setLabel(label);
	p_sprite[m_sprite_count] = sprite;
	m_sprite_count++;
	writeLog("", "Sprite '%s' loaded.", label.c_str());
	return 0;
}

std::string df::ResourceManager::getLine(std::ifstream* p_file) {
	std::string line;
	std::getline(*p_file, line);
	if (!p_file) {
		writeLog("ERROR", "File input error.");
		return "";
	}
	discardCR(line);
	return line;
}

std::vector<std::string> df::ResourceManager::readData(std::ifstream* p_file, std::string delimiter) {
	std::vector<std::string> data;
	std::string begin = "<" + delimiter + ">", end = "</" + delimiter + ">", s = getLine(p_file);
	if (s != begin) {
		writeLog("ERROR", "Sprite Error: %s not defined.", delimiter.c_str());
		data.clear();
		return data;
	}
	s = getLine(p_file);
	while (s != end && !s.empty()) {
		data.push_back(s);
		s = getLine(p_file);
	}
	if (s.empty()) {
		writeLog("ERROR", "Sprite Error: %s not closed.", delimiter.c_str());
		data.clear();
		return data;
	}
	return data;
}

int df::ResourceManager::matchLineInt(std::vector<std::string>* p_data, const char* token) {
	auto i = p_data->begin();
	int number = -1;
	while (i != p_data->end()) {
		if (i->compare(0, strlen(token), token) == 0) {
			number = atoi(i->substr(std::strlen(token) + 1).c_str());
			i = p_data->erase(i);
		}
		else {
			i++;
		}
	}
	return number;
}

std::string df::ResourceManager::matchLineStr(std::vector<std::string>* p_data, const char* token) {
	auto i = p_data->begin();
	std::string s = "";
	while (i != p_data->end()) {
		if (i->compare(0, strlen(token), token) == 0) {
			s = i->substr(strlen(token) + 1).c_str();
			i = p_data->erase(i);
		}
		else {
			i++;
		}
	}
	return s;
}

df::Frame df::ResourceManager::matchFrame(std::vector<std::string>* p_data, int width, int height) {
	if (p_data->empty()) {
		writeLog("ERROR", "Error loading sprite frame: Frame does not exist.");
		return df::Frame();
	}
	std::string line, frame_str = "";
	for (int i = 1; i <= height; i++) {
		line = p_data->front();
		if (line.length() != width) {
			return df::Frame();
		}
		p_data->erase(p_data->begin());
		frame_str += line;
	}
	line = p_data->front();
	if (line != END_FRAME_TOKEN) {
		return df::Frame();
	}
	p_data->erase(p_data->begin());
	return df::Frame(width, height, frame_str);
}

int df::ResourceManager::unloadSprite(std::string label) {
	writeLog("", "Unloading sprite '%s'.", label.c_str());
	for (int i = 0; i < m_sprite_count; i++) {
		if (p_sprite[i] != NULL) {
			if (label == p_sprite[i]->getLabel()) {
				delete p_sprite[i];
				for (int j = i; j < m_sprite_count - 1; j++) {
					p_sprite[j] = p_sprite[j + 1];
				}
				m_sprite_count--;
				writeLog("", "Sprite '%s' unloaded.", label.c_str());
				return 0;
			}
		}
	}
	writeLog("ALERT", "Cannot unload sprite '%s'. Sprite not found.", label.c_str());
	return -1;
}

void df::ResourceManager::discardCR(std::string& str) {
	if (str.size() > 0 && str[str.size() - 1] == '\r') {
		str.erase(str.size() - 1);
	}
}

df::Sprite* df::ResourceManager::getSprite(std::string label) const {
	for (int i = 0; i < m_sprite_count; i++) {
		if (label == p_sprite[i]->getLabel()) {
			return p_sprite[i];
		}
	}
	return NULL;
}

int df::ResourceManager::loadSound(std::string filename, std::string label) {
	writeLog("", "Loading sound '%s'", label.c_str());
	if (m_sound_count >= MAX_SOUNDS) {
		writeLog("ERROR", "ALERT", "Unable to load sound '%s'. Sound array full.", label.c_str());
		return -1;
	}
	for (int i = 0; i < m_sound_count; i++) {
		if (label == m_sound[i].getLabel()) {
			writeLog("ALERT", "Cannot load sound with label '%s'. '%s' already loaded.", label.c_str(), label.c_str());
			return -1;
		}
	}
	if (m_sound[m_sound_count].loadSound(filename) == -1) {
		writeLog("ALERT", "Unable to load sound '%s' from file '%s'.", label.c_str(), filename.c_str());
		return -1;
	}
	m_sound[m_sound_count].setLabel(label);
	m_sound_count++;
	writeLog("", "Sound '%s' loaded.", label.c_str());
	return 0;
}

int df::ResourceManager::unloadSound(std::string label) {
	writeLog("", "Unloading sound '%s'.", label.c_str());
	for (int i = 0; i < m_sound_count; i++) {
		if (label == m_sound[i].getLabel()) {
			for (int j = i; j < m_sound_count - 1; j++) {
				m_sound[j] = m_sound[j + 1];
			}
			m_sound_count--;
			writeLog("", "Sound '%s' unloaded.", label.c_str());
			return 0;
		}
	}
	writeLog("ALERT", "Cannot unload sound '%s'. Sound not found.", label.c_str());
	return -1;
}

df::Sound* df::ResourceManager::getSound(std::string label) {
	for (int i = 0; i < m_sound_count; i++) {
		if (label == m_sound[i].getLabel()) {
			return &m_sound[i];
		}
	}
	return NULL;
}

int df::ResourceManager::loadMusic(std::string filename, std::string label) {
	writeLog("", "Loading music '%s'", label.c_str());
	if (m_music_count >= MAX_MUSICS) {
		writeLog("ERROR", "ALERT", "Unable to load music '%s'. Sound array full.", label.c_str());
		return -1;
	}
	for (int i = 0; i < m_music_count; i++) {
		if (label == m_music[i].getLabel()) {
			writeLog("ALERT", "Cannot load music with label '%s'. '%s' already loaded.", label.c_str(), label.c_str());
			return -1;
		}
	}
	if (m_music[m_music_count].loadMusic(filename) == -1) {
		writeLog("ALERT", "Unable to load music '%s' from file '%s'.", label.c_str(), filename.c_str());
		return -1;
	}
	m_music[m_music_count].setLabel(label);
	m_music_count++;
	writeLog("", "Music '%s' loaded.", label.c_str());
	return 0;
}

int df::ResourceManager::unloadMusic(std::string label) {
	writeLog("", "Unloading music '%s'.", label.c_str());
	for (int i = 0; i < m_music_count; i++) {
		if (label == m_music[i].getLabel() && m_music[i].getLoaded()) {
			m_music[i].setLoaded(false);
			writeLog("", "Music '%s' unloaded.", label.c_str());
			return 0;
		}
	}
	writeLog("ALERT", "Cannot unload music '%s'. Music not found.", label.c_str());
	return -1;
}

df::Music* df::ResourceManager::getMusic(std::string label) {
	for (int i = 0; i < m_music_count; i++) {
		if (label == m_music[i].getLabel()) {
			return &m_music[i];
		}
	}
	return NULL;
}