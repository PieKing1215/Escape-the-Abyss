/**
	@file ObjectList.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __OBJECT_LIST_H__
#define __OBJECT_LIST_H__

// Engine includes.
#include "Object.h"
#include "ObjectListIterator.h"

namespace df {
	const int MAX_OBJECTS = 5000;
	class ObjectListIterator;
	class ObjectList {
	private:
		bool allow_duplicates; // Allow duplicate objects in list. Only checks on insertion.
		int max_count; // Max size of list.
		int m_count; // Number of items in list.
		Object** m_p_obj; // Array of pointers to objects.
		// Scale m_p_obj to a new size. Will truncate any overflow.
		// Return true if successful, false otherwise.
		bool scale(float scale);
	public:
		friend class ObjectListIterator; // Iterators can access.
		// Default constructor.
		ObjectList();
		// Copy constructor.
		ObjectList(const ObjectList& other);
		// Destructor.
		~ObjectList();
		// == operation.
		bool operator==(const ObjectList& rhs);
		// + operation.
		ObjectList operator+(ObjectList list);
		// Insert object pointer in list.
		// Return 0 if ok, else -1.
		int insert(Object* p_o);
		// Remove object pointer from list,
		// Return 0 if found, else -1.
		int remove(Object* p_o);
		// Clear list (setting count to 0).
		bool clear();
		// Return count of number of objects in list.
		int getCount() const;
		// Return true if list is empty, else false.
		bool isEmpty() const;
		// Return true if list is full, else false.
		bool isFull() const;
		// Return the max count.
		int getMaxCount() const;
		// Return the list.
		Object** getList() const;
		// Set duplicates allowed
		void setAllowDuplicates(bool new_allow = true);
		// Return allow_duplicates
		bool areDuplicatesAllowed() const;
	};
} // end of namespace df
#endif // __OBJECT_LIST_H__