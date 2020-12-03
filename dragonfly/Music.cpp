#include "Music.h"

// Engine includes.
#include "LogManager.h"

df::Music::Music() {
	m_loaded = false;
	m_music;
	m_label = "";
}

df::Music::Music(Music const&) {
	m_loaded = false;
	m_music;
	m_label = "";
}

void df::Music::operator=(df::Music const&) { }

int df::Music::loadMusic(std::string filename) {
	if (!m_music.openFromFile(filename)) {
		LM.writeLog("ERROR", "Music", "Error loading music from file '%s'", filename.c_str());
		return -1;
	}
	setLoaded();
	return 0;
}

void df::Music::setLabel(std::string new_label) {
	m_label = new_label;
}

std::string df::Music::getLabel() const {
	return m_label;
}

void df::Music::play(bool loop) {
	m_music.setLoop(loop);
	m_music.play();
}

void df::Music::stop() {
	m_music.stop();
}

void df::Music::pause() {
	m_music.pause();
}

sf::Music* df::Music::getMusic() {
	return &m_music;
}

void df::Music::setLoaded(bool loaded) {
	m_loaded = loaded;
}

bool df::Music::getLoaded() const {
	return m_loaded;
}