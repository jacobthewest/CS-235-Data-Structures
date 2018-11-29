/**********************
Jacob West
Lab 06
CS 235 Section 1
jacobthewest@gmail.com
**********************/

#ifndef STACK_H
#define STACK_H

#include "Deque.h"
template <typename T>
class Stack
{
private:
	Deque<T> stack_;
public:
	Stack(void) {};
	~Stack(void) {};
	string push(const T& value) {
		stack_.push_back(value);
		if (stack_.back() == value) {
			return "OK";
		}
		else {
			return "Error in stack_.push(const T&) or related function";
		}
	}
	void pop() {
		stack_.pop_back();
	}
	T& top() {
		return stack_.back();
	}
	size_t size() {
		return stack_.size();
	}
	T& at(size_t value) {
		return stack_.at(value);
	}
	string toString() const {
		return stack_.toString();
	}
};

#endif // STACK_H