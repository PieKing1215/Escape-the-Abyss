/**
	Utilitie functions.
	@file utility.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "utility.h"

// Engine includes.
#include "LogManager.h"
#include "WorldManager.h"

// System includes.
#include <cmath>
#include <sstream>
#include <fstream>
#include <Windows.h>

SYSTEMTIME systemtime;

static unsigned long g_next = df::getTime();

bool df::positionsIntersect(df::Vector p1, df::Vector p2) {
	int within = 1;
	return (abs(p1.getX() - p2.getX()) <= within && abs(p1.getY() - p2.getY()) <= within);
}

bool df::boxIntersectsBox(df::Box A, df::Box B) {
	df::Vector aCorner = A.getCorner(), bCorner = B.getCorner();
	// x1 true if bCorner is within A horizontally
	// x2 true if aCorner is within B horizontally
	// x3 true if bCorner is within A vertically
	// x4 true if aCorner is within B vertically
	bool x1 = bCorner.getX() <= aCorner.getX() && aCorner.getX() <= bCorner.getX() + B.getHorizontal(), x2 = aCorner.getX() <= bCorner.getX() && bCorner.getX() <= aCorner.getX() + A.getHorizontal(),
		y1 = bCorner.getY() <= aCorner.getY() && aCorner.getY() <= bCorner.getY() + B.getVertical(), y2 = aCorner.getY() <= bCorner.getY() && bCorner.getY() <= aCorner.getY() + A.getVertical();
	return (x1 || x2) && (y1 || y2);
}

bool df::boxContainsPosition(df::Box box, df::Vector pos) {
	return df::boxIntersectsBox(box, df::Box(pos, 0, 0));
}

bool df::valueInRange(float value, float min, float max) {
	return (value >= min && value <= max);
}

df::Box df::getWorldBox(const df::Object* p_o) {
	return df::getWorldBox(p_o, p_o->getPosition());
}

df::Box df::getWorldBox(const Object* p_o, df::Vector where) {
	df::Box box = ((Object*)p_o)->getBox();
	return df::Box(where + box.getCorner(), box.getHorizontal(), box.getVertical());
}

df::Vector df::worldToView(df::Vector world_pos) {
	df::Vector view_corner = WM.getView().getCorner();
	return df::Vector(world_pos.getX() - view_corner.getX(), world_pos.getY() - view_corner.getY());
}

df::Vector df::viewToWorld(df::Vector view_pos) {
	df::Vector view_corner = WM.getView().getCorner();
	return df::Vector(view_pos.getX() + view_corner.getX(), view_pos.getY() + view_corner.getY());
}

std::string df::toString(int i) {
	return std::to_string(i);
}

std::string df::toString(float i) {
	return std::to_string(i);
}

std::string df::toString(long i) {
	std::stringstream ss;
	ss << i;
	return ss.str();
}

std::string df::toString(unsigned long i) {
	std::stringstream ss;
	ss << i;
	return ss.str();
}

std::string df::toString(df::Vector i) {
	return toString(i.getX()) + " " + toString(i.getY());
}

std::string df::toString(df::Box i) {
	return toString(i.getCorner()) + " " + toString(i.getHorizontal()) + " " + toString(i.getVertical());
}

long int df::getTime() {
	GetSystemTime(&systemtime);
	return ((systemtime.wHour * 3600000) + (systemtime.wMinute * 60000) + (systemtime.wSecond * 1000) + systemtime.wMilliseconds);
}

std::string df::getTimeString() {
	GetSystemTime(&systemtime);
	static char time_str[13];
	long int time = getTime();
	sprintf_s(time_str, "%02d:%02d:%02d.%03d", systemtime.wHour, systemtime.wMinute, systemtime.wSecond, systemtime.wMilliseconds);
	time_str[12] = '\0';
	return time_str;
}

int df::rand() {
	srand(g_next);
	return rand();
}

int df::rand(unsigned long seed) {
	srand(seed);
	g_next = seed;
	return rand();
}

std::string df::getLine(std::ifstream* p_file) {
	std::string line;
	std::getline(*p_file, line);
	if (!p_file) {
		return "";
	}
	df::discardCR(line);
	return line;
}

void df::discardCR(std::string& str) {
	if (str.size() > 0 && str[str.size() - 1] == '\r') {
		str.erase(str.size() - 1);
	}
}