/**
	@file ObjectListIterator.h
	@author Dennis James Stelmach (dstelmach2@wpi.edu)
*/
#pragma once

#ifndef __OBJECT_LIST_ITERATOR_H__
#define __OBJECT_LIST_ITERATOR_H__

// Engine includes.
#include "Object.h"
#include "ObjectList.h"

namespace df {
	class ObjectList;
	class ObjectListIterator {
	private:
		ObjectListIterator(); // Iterator must be given list when created.
		int m_index; // Index into list.
		const ObjectList* m_p_list;	// List iterating over.
	public:
		// Create iterator, over indicated list.
		ObjectListIterator(const ObjectList* p_list);
		// Set iterator to first item in list.
		void first();
		// Set iterator to next item in list.
		void next();
		// Return true if at end of list.
		bool isDone() const;
		// Return pointer to current item in list, NULL if done/empty.
		Object* currentObject() const;
	};
} // end of namespace df
#endif // __OBJECT_LIST_ITERATOR_H__