/**********************
Jacob West
Lab 06
CS 235 Section 1
jacobthewest@gmail.com
**********************/

#ifndef STATION_H
#define STATION_H

#include "Deque.h"
#include "Queue.h"
#include "Stack.h"
#include "Vector.h"
template <typename T>
class Station
{
private:
	Vector<T> train_;
	Stack<T> stack_;
	Queue<T> queue_;
	T turnTableCar_;
	bool empty;
public:
	Station(void) { empty = true; };
	~Station(void) {};
	//Train car enters the station turntable. 
	string addCar(const T& value) {
		if (!empty) {
			return "Turntable occupied!";
		}
		else {
			turnTableCar_ = value;
			empty = false;
			return "OK";
		}		
	}
	//A train car is removed from the turntable and pushed into the train vector.
	string removeCar() {
		if (empty) {
			return "Turnatable empty!";
		}
		else {
			train_.push_back(turnTableCar_); //Push to train vector
			empty = true;
			return "OK";
		}
	}
	//Display the current train car on station turntable
	string topCar() {
		if (empty) {
			return "Turntable empty!";
		}
		else {
			return std::to_string(turnTableCar_);
		}
	}
	//Train car is removed from the turntable and pushed to the Stack roundhouses
	string addStack() {
		if (empty) {
			return "Turnatable empty!";
		}
		else {			
			empty = true;
			return stack_.push(turnTableCar_); //Push to stack roundhouse
		}
	}
	//A train car is removed from Stack roundhouse and moved to the station turntable
	string removeStack() {
		if (stack_.size() == 0) {
			return "Stack empty!";
		}
		else {
			string sMessage = addCar(stack_.top());
			stack_.pop();
			return sMessage;
		}
	}
	//Display the train car at head of Stack roundhouse.
	string topStack() {
		if (stack_.size() == 0) {
			return "Stack empty!";
		}
		else {
			return std::to_string(stack_.top());
		}
	}
	//Output number of train cars in Stack roundhouse
	string sizeStack() {
		return std::to_string(stack_.size());
	}
	//Train car is removed from the turntable and pushed to the Queue roundhouse.
	string addQueue() {
		if (empty) {
			return "Turnatable empty!";
		}
		else {
			queue_.push(turnTableCar_); //Push to the queue roundhouse
			empty = true;
			return "OK";
		}
	}
	//A train car is removed from Queue roundhouse and moved to the station turntable. 
	string removeQueue() {
		if (queue_.size() == 0) {
			return "Queue empty!";
		}
		else if (!empty){
			return "Turntable occupied!";
		}
		else {
			turnTableCar_ = queue_.top();
			empty = false;
			queue_.pop();
			return "OK";
		}
	}
	//Display the train car at head of Queue roundhouse.
	string topQueue() {
		if (queue_.size() == 0) {
			return "Queue empty!";
		}
		else {
			return std::to_string(queue_.top());
		}		
	}
	//Output number of train cars in Queue roundhouse
	string sizeQueue() {
		return std::to_string(queue_.size());
	}
	//string find(T);
	//Output the contents of the train vector.
	string legitToString() {
		return train_.legitToString();
	}
};

#endif // STATION_H