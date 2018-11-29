/**********************
Jacob West
Lab 09
CS 235 Section 1
jacobthewest@gmail.com
**********************/

//Wrapped class to include a binary search tree
#ifndef SET_H
#define SET_H

#include "BST.h"
#include "SetInterface.h"
#include <sstream>

template<typename T>
class Set : public SetInterface<T>
{
private:
	BST<T> set;
public:
	Set() {}
	~Set() {};

	/** Inserts item into the set, if the container doesn't
	already contain an element with an equivalent value.
	@return: pair.first = pointer to item
	pair.second = true if successfully inserted, else false. */
	//virtual Pair<T*, bool> insert(const T& item) = 0;
	virtual bool insert(const T& item) {
		return set.addNode(item);
	}

	/** @return: the number of elements removed from the Set. */
	virtual size_t erase(const T& item) {
		return 666; //:)
		/*size_t elementsBefore = set.getNumNodes();
		size_t elementsAfter;
		
		while (set.removeNode(item)) {
			elementsAfter = set.getNumNodes();
		}
		size_t numElementsRemoved = elementsBefore - elementsAfter;
		return numElementsRemoved;*/
	}

	/** @return: true if the item was deleted */
	bool remove(T& item) {
		return set.removeNode(item);
	}

	/** Removes all items from the set. */
	virtual void clear() {
		set.clearTree();
	}

	/** @return: the number of elements contained by the Set. */
	virtual size_t size() const {
		return set.getNumNodes();
	}

	/** @return: return 1 if contains element equivalent to item, else 0. */
	virtual size_t count(const T& item) const {
		return 666; //:)
	}

	/** @return: return 1 if contains element equivalent to item, else 0. */
	size_t legitCount(const T& item) {
		if (set.findNode(item)) {
			return 1;
		}
		else {
			return 0;
		}
	}

	/** @return: string representation of items in Set. */
	std::string toString() const {
		return "This funcion is dumb";
	}

	/** @return: string representation of items in Set. */
	std::string toStringLegit() {
		return set.toStringAlphabetical();
	}
};
#endif // SET_H