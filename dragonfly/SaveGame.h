/**
	@file SaveGame.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __SAVE_GAME_H__
#define __SAVE_GAME_H__

#include <string>

namespace df {
	class SaveGame {
	public:
		// Return this object built as a string.
		virtual std::string getSaveString();
		// Parse the save string into usable variables.
		// Return 0 if ok. -1 if error.
		virtual int loadSaveString(std::string key, std::string value);
	};
} // end of namespace df
#endif // __SAVE_GAME_H__
