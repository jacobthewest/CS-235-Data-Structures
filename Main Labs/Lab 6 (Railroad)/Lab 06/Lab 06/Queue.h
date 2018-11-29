/**********************
Jacob West
Lab 06
CS 235 Section 1
jacobthewest@gmail.com
**********************/

#ifndef QUEUE_H
#define QUEUE_H

#include "Deque.h"
template <typename T>
class Queue
{
private:
	Deque<T> queue_;
public:
	Queue() {};
	~Queue(void) {};
	/** Returns "OK" if successful. Inserts a car at the end of the container ***/
	string push(const T& value) {
		queue_.push_back(value);
		if (queue_.back() == value) {
			return "OK";
		}	
		else {
			return "Error in queue.push or related function";
		}
	}
	/** Removes the oldest element in the container **/
	void pop() {
		return queue_.pop_front();
	}
	/** Returns the top element of the container **/
	T& top() {
		return queue_.front();
	}
	/** Returns the size of the containers **/
	size_t size() {
		return queue_.size();
	}
	/** Returns the element at the desired index (0 based) **/
	T& at(size_t index) {
		int iPos = index;
		return queue_.at(iPos);
	}
	/** Returns all of the elements of the container as a string **/
	string toString() const {
		return queue_.toString();
	}
};

#endif // QUEUE_H