/**
	@file Music.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __MUSIC_H__
#define __MUSIC_H__

// System includes.
#include <string>
#include <SFML/Audio.hpp>

namespace df {

	class Music {

	private:
		bool m_loaded; // True if a song is ready to play.
		sf::Music m_music; // The SFML music.
		std::string m_label; // Text label to identify music.
		Music(Music const&); // SFML doesn't allow music copy.
		void operator=(Music const&); // SFML doesn't allow music assignment.
	public:
		Music();

		// Associate music buffer with file.
		// Return 0 if ok, else -1.
		int loadMusic(std::string filename);

		// Set label associated with music.
		void setLabel(std::string new_label);

		// Get label associated with music.
		std::string getLabel() const;

		// Play music.
		// If loop is true, repeat play when done.
		void play(bool loop = true);

		// Stop music.
		void stop();

		// Pause music.
		void pause();

		// Return pointer to SFML music.
		sf::Music* getMusic();

		// Set if this Object is ready.
		void setLoaded(bool loaded = true);

		// Get if this Object is ready.
		bool getLoaded() const;
	};

} // end of namespace df
#endif // __MUSIC_H__
