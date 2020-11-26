/**
	@file LogManager.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__

// Engine includes.
#include "Manager.h"

// Two-letter acronym for easier access to manager.
#define LM df::LogManager::getInstance()

namespace df {
	const std::string LOGFILE_DEFAULT = "dragonfly.log";
	class LogManager : public Manager {
	private:
		// Private since a singleton.
		LogManager();
		// Don't allow copy.
		LogManager(LogManager const&);
		// Don't allow assignment.
		void operator=(LogManager const&);
		bool m_do_flush; // True if flush to disk after write.
		FILE* m_p_f; // Pointer to main logfile.
	public:
		// If logfile is open, close it.
		~LogManager();
		// Get the one and only instance of the LogManager.
		static LogManager& getInstance();
		// Start up LogManager (open main logfile, usually "dragonfly.log").
		// Return 0 if ok, else -1.
		int startUp();
		// Shut down LogManager (close all logfiles).
		void shutDown();
		// Write to logfile.
		// Supports printf() formatting of strings.
		// Return number of bytes written, -1 if error.
		// It is discouraged to use this directly and instead use writeLog provided by df::Manager, df::Object, and df::Sprite as they provide details about the reporter.
		int writeLog(std::string warn, std::string reporter, const char* fmt, ...) const;
		int writeLog(std::string warn, std::string reporter, const char* fmt, va_list args) const;
		// Set flush of logfile after each write.
		void setFlush(bool new_do_flush = true);
	};
} // end of namespace df
#endif // __LOG_MANAGER_H__
