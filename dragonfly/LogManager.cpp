/**
	Log manager.
	@file LogManager.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "LogManager.h"

// Engine includes.
#include "utility.h"

// System includes.
#include <stdarg.h>
#include <stdexcept>

df::LogManager::LogManager() {
	df::Manager::setType("LogManager");
	m_do_flush = false;
	m_p_f = NULL;
}

df::LogManager::LogManager(LogManager const&) {
	df::Manager::setType("LogManager");
	m_do_flush = false;
	m_p_f = NULL;
}

df::LogManager::~LogManager() {

}

void df::LogManager::operator=(LogManager const&) {

}

df::LogManager& df::LogManager::getInstance() {
	static LogManager logManager;
	return logManager;
}

int df::LogManager::startUp() {
	fopen_s(&m_p_f, LOGFILE_DEFAULT.c_str(), "w"); // Open log file.
	if (m_p_f == NULL) {
		return -1;
	}
	int x = fprintf(m_p_f, "Dragonfly by Dennis James Stelmach following the Dragonfly book available at https://dragonfly.wpi.edu/book/");
	if (x < 0) { // Hide a test write as the start up message.
		return -1;
	}
	df::Manager::startUp();
	return 0;
}

void df::LogManager::shutDown() {
	df::Manager::writeLog("", "Stopping...");
	fclose(m_p_f);
	df::Manager::shutDown();
}

int df::LogManager::writeLog(std::string warn, std::string reporter, const char* fmt, ...) const {
	va_list args;
	va_start(args, fmt);
	int rc = writeLog(warn, reporter, fmt, args);
	va_end(args);
	return rc;
}

int df::LogManager::writeLog(std::string warn, std::string reporter, const char* fmt, va_list args) const {
	int x = fprintf_s(m_p_f, "\n%-5s | %s | %-16s | ", warn.c_str(), df::getTimeString().c_str(), reporter.c_str());
	x += vfprintf_s(m_p_f, fmt, args);
	if (x > 0 && m_do_flush) {
		fflush(m_p_f);
	}
	return x;
}

void df::LogManager::setFlush(bool new_do_flush) {
	m_do_flush = new_do_flush;
}