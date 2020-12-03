/**
	Scene Graph.
	@file SceneGraph.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "SceneGraph.h"

// Engine includes.
#include "LogManager.h"
#include "utility.h"

df::SceneGraph::SceneGraph() {
	m_active_objects;
	m_inactive_objects;
	m_solid_objects;
	m_visible_objects;
}

int df::SceneGraph::insertObject(df::Object* p_o) {
	LM.writeLog("", "SceneGraph", "Inserting object '%s %d'", p_o->getType().c_str(), p_o->getId());
	if (!df::valueInRange(p_o->getAltitude(), 0, df::MAX_ALTITUDE)) {
		LM.writeLog("ERROR", "SceneGraph", "Error inserting object. Object altitude not in range.");
		return -1;
	}
	df::ObjectList ol = m_active_objects + m_inactive_objects;
	df::ObjectListIterator li(&ol);
	li.first();
	while (!li.isDone() && li.currentObject()) {
		if (li.currentObject() == p_o) {
			return 0; // Already inserted.
		}
		li.next();
	}
	if (p_o->isActive()) {
		m_active_objects.insert(p_o);
	}
	else {
		m_inactive_objects.insert(p_o);
	}
	if (p_o->isSolid()) {
		m_solid_objects.insert(p_o);
	}
	m_visible_objects[p_o->getAltitude()].insert(p_o);
	return 0;
}

int df::SceneGraph::removeObject(df::Object* p_o) {
	if (m_active_objects.remove(p_o) == 0) {
		if (p_o->isSolid()) {
			m_solid_objects.remove(p_o);
		}
		m_visible_objects[p_o->getAltitude()].remove(p_o);
		return 0;
	}
	return -1;
}

df::ObjectList df::SceneGraph::activeObjects() const {
	return m_active_objects;
}

df::ObjectList df::SceneGraph::solidObjects() const {
	return m_solid_objects;
}

df::ObjectList df::SceneGraph::visibleObjects(int altitude) const {
	return m_visible_objects[altitude];
}

df::ObjectList df::SceneGraph::inactiveObjects() const {
	return m_inactive_objects;
}

int df::SceneGraph::updateAltitude(df::Object* p_o, int new_alt) {
	if (!df::valueInRange(new_alt, 0, df::MAX_ALTITUDE)) {
		LM.writeLog("ERROR", "SceneGraph", "Error inserting object. Object altitude not in range.");
		return -1;
	}
	if (p_o->getAltitude() == new_alt) {
		return 0; // Altitude hasn't changed
	}
	m_visible_objects[p_o->getAltitude()].remove(p_o);
	m_visible_objects[new_alt].insert(p_o);
	return 0;
}

int df::SceneGraph::updateSolidness(df::Object* p_o, df::Solidness new_solidness) {
	if (p_o->isSolid() == (new_solidness == df::Solidness::HARD || new_solidness == df::Solidness::SOFT)) {
		return 0; // Solidness hasn't changed
	}
	if (p_o->isSolid()) {
		m_solid_objects.remove(p_o);
	}
	if (new_solidness == df::Solidness::HARD || new_solidness == df::Solidness::SOFT) {
		m_solid_objects.insert(p_o);
	}
	return 0;
}

int df::SceneGraph::updateVisible(df::Object* p_o, bool new_visible) {
	if (p_o->isVisible() == new_visible) {
		return 0; // Visibility hasn't changed
	}
	if (new_visible) {
		m_visible_objects[p_o->getAltitude()].insert(p_o);
	}
	else {
		m_visible_objects[p_o->getAltitude()].remove(p_o);
	}
	return 0;
}

int df::SceneGraph::updateActive(df::Object* p_o, bool new_active) {
	if (p_o->isActive() == new_active) {
		return 0; // Active hasn't changed
	}
	if (p_o->isActive()) {
		m_active_objects.remove(p_o);
		m_inactive_objects.insert(p_o);
	}
	else {
		m_inactive_objects.remove(p_o);
		m_active_objects.insert(p_o);
	}
	return 0;
}