/**********************
Jacob West
Lab 06
CS 235 Section 1
jacobthewest@gmail.com
**********************/

#ifndef VECTOR_H
#define VECTOR_H

#include "Deque.h"
template <typename T>
class Vector
{
private:
	Deque<T> vector_;
public:
	Vector(void) {};
	~Vector(void) {};
	void push_back(const T& value) {
		return vector_.push_back(value);
	}
	void pop_back() {
		return vector_.pop_back();
	}
	T& back() {
		return vector_.back();
	}
	size_t size() {
		return vector_.size();
	}
	/*
	T atNoSuck(size_t position) {
		return vector_atNoSuck(position);
	}
	*/
	/** Return the deque items */
	virtual string legitToString() {
		return vector_.legitToString();
	}
	string toString() const {
		return vector_.toString();
	}
};

#endif // VECTOR_H