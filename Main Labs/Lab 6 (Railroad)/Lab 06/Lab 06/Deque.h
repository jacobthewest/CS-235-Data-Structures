/**********************
Jacob West
Lab 06
CS 235 Section 1
jacobthewest@gmail.com
**********************/

#ifndef DEQUE_H
#define DEQUE_H

#include "DequeInterface.h"

#include <iostream>
#include <array>
#include <sstream>
#include <string>

template<typename T>
class Deque : public DequeInterface<T> {
private:
	size_t capacity;
	size_t num_items;
	size_t front_index;
	size_t rear_index;
	T * the_data;
	void reallocate() {
		size_t new_capacity = 2 * capacity;
		T* new_data = new T[new_capacity];
		size_t j = front_index;
		for (size_t i = 0; i < num_items; i++) {
			new_data[i] = the_data[j];
			j = (j + 1) % capacity;
		}
		front_index = 0;
		rear_index = num_items - 1;
		capacity = new_capacity;
		std::swap(the_data, new_data);

		delete[] new_data;
	}
	static const size_t DEFAULT_CAPACITY = 4;
public:
	Deque(void) :
		capacity(DEFAULT_CAPACITY),
		num_items(0),
		front_index(0),
		rear_index(DEFAULT_CAPACITY - 1),
		the_data(new T[DEFAULT_CAPACITY]) {};
	~Deque(void) { delete[] the_data; };
	/** Insert item at front of deque */
	void push_front(const T& value) {

		if (num_items == capacity) {
			reallocate();
		}

		front_index = (front_index - 1) % capacity;
		the_data[front_index] = value;

		num_items++;
	}
	/** Insert item at rear of deque */
	void push_back(const T& value) {

		if (num_items == capacity) {
			reallocate();
		}
		rear_index = (rear_index + 1) % capacity;
		the_data[rear_index] = value;
		
		num_items++;
	}
	/** Remove the front item of the deque */
	void pop_front(void) {
		//Is the array empty?
		if (num_items == 0) {
			throw string("The deque is empty, this is impossible");
		}
		else {			
			front_index = (front_index + 1) % capacity;
		}
		num_items--;
	}
	/** Remove the rear item of the deque */
	void pop_back(void) {
		if (num_items == 0) {
			throw string("The deque is empty, this is impossible");
		}
		else {
			rear_index = (rear_index - 1) % capacity; //Set the new rear_index to be 1 less than itself
		}
		num_items--;
	}
	/** Return the front item of the deque (Do not remove) */
	T& front(void) {
		return the_data[front_index];
	}
	/** Return the rear item of the deque (Do not remove) */
	T& back(void) {
		return the_data[rear_index];
	}
	/** Return the number of items in the deque */
	size_t size(void) const {
		return num_items;
	}
	/** Return true if deque is empty */
	 bool empty(void) const {
		if (num_items == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	/** Return item in deque at index (0 based) */
	T& at(size_t index) {
		unsigned int iCnt = 0;
		while (iCnt != index) {
			iCnt++;
		}
		return the_data[iCnt % num_items];
	}
	T atNoSuck(size_t index) {
		
		return the_data[front_index + (index % num_items)];
	}
	/** Return the deque items */
	string legitToString() {
		std::ostringstream oss;

		unsigned int iCnt = front_index;
		while (iCnt != rear_index) {
			T reference = (atNoSuck(iCnt));
			oss << reference << " ";
			iCnt = (iCnt + 1) % capacity;
		}
		oss << at(rear_index) << " ";
		return oss.str();
	}
	/** Return the deque items */
	string toString() const {
		return "The at function should have been const as well";
	}
};
#endif // DEQUE_H