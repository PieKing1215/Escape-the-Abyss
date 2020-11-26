/**
	Iterator for ObjectList.
	@file ObjectListIterator.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "ObjectListIterator.h"

df::ObjectListIterator::ObjectListIterator() {
	m_p_list = NULL;
	first();
}

df::ObjectListIterator::ObjectListIterator(const ObjectList* p_list) {
	m_p_list = p_list;
	first();
}

void df::ObjectListIterator::first() {
	m_index = 0;
}

void df::ObjectListIterator::next() {
	if (m_index < m_p_list->getCount()) {
		m_index++;
	}
}

bool df::ObjectListIterator::isDone() const {
	return (m_index == m_p_list->getCount());
}

df::Object* df::ObjectListIterator::currentObject() const {
	return m_p_list->m_p_obj[m_index];
}