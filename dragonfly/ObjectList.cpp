/**
	Object list.
	@file ObjectList.cpp
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/

#include "ObjectList.h"

// Engine includes.
#include "LogManager.h"

df::ObjectList::ObjectList() {
	allow_duplicates = false;
	max_count = 1;
	m_count = 0;
	m_p_obj = (df::Object**)(malloc(sizeof(df::Object*)));
}

df::ObjectList::ObjectList(const df::ObjectList& other) {
	allow_duplicates = false;
	max_count = other.getMaxCount();
	m_count = other.getCount();
	m_p_obj = (Object**)(malloc(sizeof(Object*) * max_count));
	if (m_p_obj != NULL) {
		memcpy(m_p_obj, other.getList(), sizeof(Object*) * max_count);
	}
}

df::ObjectList::~ObjectList() {
	// Freeing the memory here causes a read violation on shutdown. Shouldn't really matter, but it should be known.
	//free(m_p_obj);
}

bool df::ObjectList::operator==(const df::ObjectList& rhs) {
	return (max_count == rhs.getMaxCount() && m_count == rhs.getCount() && m_p_obj == rhs.getList());
}

df::ObjectList df::ObjectList::operator+(df::ObjectList list) {
	df::ObjectList big_list = *this;
	df::ObjectListIterator li(&list);
	li.first();
	while (!li.isDone() && li.currentObject()) {
		big_list.insert(li.currentObject());
		li.next();
	}
	return big_list;
}

int df::ObjectList::insert(df::Object* p_o) {
	if (!p_o) {
		return -1;
	}
	if (!allow_duplicates) {
		for (int i = 0; i < m_count; i++) {
			if (m_p_obj[i] == p_o) {
				LM.writeLog("WARN", "ObjectList", "Insert failed due to element already in list.");
				return 0;
			}
		}
	}
	if (isFull()) {
		if (!scale(2)) {
			LM.writeLog("ERROR", "ObjectList", "Insert failed due to scale error.");
			return -1;
		}
	}
	m_p_obj[m_count] = p_o;
	m_count++;
	return 0;
}

int df::ObjectList::remove(df::Object* p_o) {
	for (int i = 0; i < m_count; i++) {
		if (m_p_obj[i] == p_o) {
			for (int j = i; j < m_count; j++) {
				m_p_obj[j] = m_p_obj[j + 1];
			}
			m_count--;
			return 0;
		}
	}
	return -1;
}

bool df::ObjectList::clear() {
	df::Object** tmp_obj = (df::Object**)(realloc(m_p_obj, sizeof(df::Object*)));
	if (tmp_obj == NULL) {
		free(tmp_obj);
		return false;
	}
	m_p_obj = tmp_obj;
	m_p_obj[0] = NULL;
	m_count = 0;
	max_count = 1;
	return true;
}

int df::ObjectList::getCount() const {
	return m_count;
}

int df::ObjectList::getMaxCount() const {
	return max_count;
}

df::Object** df::ObjectList::getList() const {
	return m_p_obj;
}

bool df::ObjectList::isEmpty() const {
	return m_count == 0;
}

bool df::ObjectList::isFull() const {
	return m_count >= max_count || m_count >= MAX_OBJECTS;
}

bool df::ObjectList::scale(float scale) {
	//LM.writeLog("", "ObjectList", "Scaling list from %d by factor of %f...", max_count, scale);
	df::Object** tmp_obj = (df::Object**)(realloc(m_p_obj, (scale * max_count * (int)sizeof(df::Object*))));
	if (tmp_obj == NULL) {
		free(tmp_obj);
		LM.writeLog("", "ObjectList", "Scale failed.");
		return false;
	}
	m_p_obj = tmp_obj;
	max_count = floor(((float)(max_count)) * scale);
	return true;
}

void df::ObjectList::setAllowDuplicates(bool new_allow) {
	allow_duplicates = new_allow;
}

bool df::ObjectList::areDuplicatesAllowed() const {
	return allow_duplicates;
}