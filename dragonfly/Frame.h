/**
	@file Frame.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __FRAME_H__
#define __FRAME_H__

// Engine includes.
#include "Color.h"
#include "Vector.h"

// System includes.
#include <string>

namespace df {

	class Frame {

	private:
		int m_width;             // Width of frame
		int m_height;            // Height of frame
		std::string m_frame_str; // All frame characters stored as string.
		char m_transparency; // Sprite transparent character (0 if none) .

	public:
		// Create empty frame.
		Frame();

		// Create frame of indicated width and height and string.
		Frame(int new_width, int new_height, std::string frame_str);

		// Create frame of indicated width and height and string and transparency.
		Frame(int new_width, int new_height, std::string frame_str, char new_transparency);

		// Set width of frame.
		void setWidth(int new_width);

		// Get width of frame.
		int getWidth() const;

		// Set height of frame.
		void setHeight(int new_height);

		// Get height of frame.
		int getHeight() const;

		// Set frame characters (stored as string).
		void setString(std::string new_frame_str);

		// Get frame characters (stored as string).
		std::string getString() const;

		// Set Sprite transparency character (0 means none).
		void setTransparency(char new_transparency);
		
		// Get Sprite transparency character (0 means none).
		char getTransparency() const;


		// Draw self centered at position (x,y) with color.
		// Return 0 if ok, else -1.
		// Note: top-left coordinate is (0,0).
		int draw(Vector position, Color color, char transparent) const;
	};

} // end of namespace df
#endif //__FRAME_H__
