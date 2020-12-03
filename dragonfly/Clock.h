/**
	@file Clock.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __CLOCK_H__
#define __CLOCK_H__

namespace df {
	class Clock {
	private:
		// Time of last delta() call.
		// Units are milliseconds.
		long int m_previous_time;
	public:
		// Sets previous_time to current time.
		Clock();
		// Return time elapsed since last delta() call. -1 if error.
		// Resets clock time.
		// Units are milliseconds.
		long int delta();
		// Return time elapsed since last delta() call. -1 if error.
		// Does not reset clock time.
		// Units are milliseconds.
		long int split() const;
	};
} // end of namespace df
#endif // __CLOCK_H__
