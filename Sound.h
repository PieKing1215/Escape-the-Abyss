/**
	@file Sound.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __SOUND_H__
#define __SOUND_H__

// System includes.
#include <string>
#include <SFML/Audio.hpp>

namespace df {

	class Sound {

	private:
		sf::Sound m_sound;	          // SFML sound.
		sf::SoundBuffer m_sound_buffer; // SFML sound buffer associated with sound.
		std::string m_label;	          // Text label to identify sound.

	public:

		// Constructor.
		Sound();

		// Destructor.
		virtual ~Sound();

		// Load sound buffer from file.
		// Return 0 if ok, else -1.
		int loadSound(std::string filename);

		// Set label associated with sound.
		void setLabel(std::string new_label);

		// Get label associated with sound.
		std::string getLabel() const;

		// Play sound.
		// If loop is true, repeat play when done.
		void play(bool loop = false);

		// Stop sound.
		void stop();

		// Pause sound.
		void pause();

		// Return SFML sound.
		sf::Sound getSound() const;
	};

} // end of namespace df
#endif // __SOUND_H__
