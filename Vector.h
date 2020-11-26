/**
	@file Vector.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __DF_VECTOR_H__
#define __DF_VECTOR_H__

namespace df {
	class Vector {
	private:
		float m_x; 			//< Horizontal component.
		float m_y; 			//< Vertical component.
	public:
		// Create Vector with (x,y).  
		Vector(float init_x, float init_y);
		// Default is (0,0).
		Vector();
		void setX(float new_x);	        // Set horizontal component.
		float getX() const;		        // Get horizontal component.
		void setY(float new_y);	        // Set vertical component.
		float getY() const;		        // Get vertical component.
		void setXY(float new_x, float new_y); // Set horizizontal & vertical.
		void normalize();			// Normalize vector.
		void scale(float s);			// Scale vector.
		float getMagnitude() const;		// Return magnitude.
		void operator=(const Vector& other); // Assign Vector.
		bool operator==(const Vector& other) const; // Compare Vector.
		bool operator==(const float& other) const; // Compare Vector.
		bool operator!=(const Vector& other) const; // Compare Vector.
		bool operator!=(const float& other) const; // Compare Vector.
		Vector operator+(const Vector& other) const; // Add Vector.
		Vector operator-(const Vector& other) const; // Subtract Vector.
		Vector operator*(const Vector& other) const; // Multiply Vector.
		Vector operator/(const Vector& other) const; // Divide Vector.
		Vector operator+(const float& other) const; // Add Vector.
		Vector operator-(const float& other) const; // Subtract Vector.
		Vector operator*(const float& other) const; // Multiply Vector.
		Vector operator/(const float& other) const; // Divide Vector.
	};
} // end of namespace df
#endif //__DF_VECTOR_H__
