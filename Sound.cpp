#include "Sound.h"

// Engine includes.
#include "LogManager.h"

df::Sound::Sound() {
	m_sound = sf::Sound();
	m_sound_buffer = sf::SoundBuffer();
	m_label = "";
}

df::Sound::~Sound() {
	m_sound.stop();
	m_sound.resetBuffer();
}

int df::Sound::loadSound(std::string filename) {
	if (!m_sound_buffer.loadFromFile(filename)) {
		LM.writeLog("ERROR", "Sound", "Error loading sound from file '%s'", filename.c_str());
		return -1;
	}
	m_sound.setBuffer(m_sound_buffer);
	return 0;
}

void df::Sound::setLabel(std::string new_label) {
	m_label = new_label;
}

std::string df::Sound::getLabel() const {
	return m_label;
}

void df::Sound::play(bool loop) {
	m_sound.setLoop(loop);
	m_sound.play();
}

void df::Sound::stop() {
	m_sound.stop();
}

void df::Sound::pause() {
	m_sound.pause();
}

sf::Sound df::Sound::getSound() const {
	return m_sound;
}