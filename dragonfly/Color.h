/**
	@file Color.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __COLOR_H__
#define __COLOR_H__

namespace df {

	// Colors Dragonfly recognizes.
	enum class Color {
		UNDEFINED_COLOR = -1,
		BLACK = 0,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE,
		ORANGE,
		CUSTOM,
	};

	// If color not specified, will use this.
	const Color COLOR_DEFAULT = df::Color::WHITE;

} // end of namespace df
#endif //__COLOR_H__
