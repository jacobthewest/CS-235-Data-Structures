/**********************
Jacob West
Lab 06
CS 235 Section 1
jacobthewest@gmail.com
**********************/
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "LinkedListInterface.h"

#include <iostream>
#include <sstream>
#include <string>

//This part of our code lets us use the letter 'T' to represent any type of data.
template<typename T> 
class LinkedList : public LinkedListInterface<T> {
public: 	
	LinkedList(void) {}
	~LinkedList(void) { clear(); }
	//Recommended to use node instead of class because it makes it easier to 
	//access date members of the "Node class"
	//A struct is like a mini class that lives inside of my class.
	struct Node {
		T data;
		Node* next;

		//Constructor
		/**creates a new Node that points to another Node.
		@param datea_item The data stroed
		@param next_ptr Pointer to the Node that is
		pointed to by the new Node
		*/
		Node(const T& data_item, Node* next_ptr = NULL) :
			data(data_item), next(next_ptr) {};
		//Node* next_ptr = NULL provides
		//NULL as a default value for next
	};

	Node* head = NULL;
	
	/** Insert Node at beginning of linked list (no duplicates) */
	virtual bool insertHead(T value) {
		if (find(value)) {
			return false; //The value already exists. Do not add
		}

		//Case 1: No current head
		if (head == NULL) {
			//Create a head
			head = new Node(value);
			return true; //We added a head.
		}
		//Case 2
		else {
			//We already have a head
			Node* newNode = new Node(value, head); //Create node
			newNode->next = head; //connects the nodes
			head = newNode; //set the correct head
			return true; //We added a head.
		}		
	}

	/** Insert Node at end of linked list (no duplicates) */
	virtual bool insertTail(T value) {
		if (find(value)) {
			return false; //The value already exists. Do not add
		}
		//Case 1: No current head
		if (head == NULL) {
			insertHead(value);
			return true;
		}
		//Case 2: There is a current head
		else {
			//We make a new node with the given info and have its next variable point to NULL
			Node* newNode = new Node(value); //Our constructor sets the next pointer by default to NULL

			//Now make a temporary pointer and have it go through our list until it finds the tail node
			Node* tempNodePointer = head; //make a temp Node and have it point to the head

			//While loop to search through list until the our temp node finds the tail node
			while (tempNodePointer->next != NULL) {
					tempNodePointer = tempNodePointer->next;
			}
			//Now the tempNode points to the last element in the list.
			tempNodePointer->next = newNode; //now newNode is at the end of the list and points to NULL
			return true;
		}
	}

	/** Insert node after matchNode (no duplicates) */
	virtual bool insertAfter(T matchNode, T node) {
		if (find(node)) {
			return false; //The value already exists. Do not insert
		}
		if (find(matchNode)) {
			//The node we want to insert after does exist in our list.
			//Find the node to insertAfter
			Node* tempNode = head;

			while (tempNode->data != matchNode) { //Search until we find the matchNode
				tempNode = tempNode->next;
			}

			//the tempNode now is equal to the matchNode;
			Node* insertedNode = new Node(node, tempNode->next); //Create our inserted node and set 
															     //its next to the tempNode's next
			tempNode->next = insertedNode; //Now point tempNode to the Inserted node
			return true; //The node was inserted
		}
		else {
			return false; //There is no item in our list that has the value
					      //of matchNode
		}

	}

	/** Remove Node from linked list */
	virtual bool remove(T value) {
		if (find(value)) { //The value exists
			//Case 1: Delete the head
			if (head->data == value) {
				Node* tempHead = head;
				head = head->next;
				delete tempHead;
				return true; //it was deleted
			}
			else { //Case 2: Delete something other than the head
				Node* nodeBeforeRemovalNode = head;
				while (nodeBeforeRemovalNode->next->data != value) {
					nodeBeforeRemovalNode = nodeBeforeRemovalNode->next;
				}

				Node* deleteThisNode = nodeBeforeRemovalNode->next;
				nodeBeforeRemovalNode->next = deleteThisNode->next;
				delete deleteThisNode;
				return true; //it was deleted
			}
		}
		else {
			return false; //Value does not exist so it was not removed
		}
	}
	virtual bool clear() {
		//Lady in the video said to call my remove function on the head
			//repeatedly until the list is empty
		while (head != NULL) {
			remove(head->data);
		}
		if (head == NULL) {
			return true; //list is now empty
		}
		else {
			return false; //list still has stuff in it
		}

	}

	/** Return Node at index (0 based) */
	virtual T at(int index) {
		if (size() == 0) {
			return T();
		}
		if (index >= size() || index < 0) {
			return T();
		}
		Node* tempNode = head;
		int iCounter = 0;
		if (index == 0) {
			return head->data;
		}
		while (iCounter != index) {
			tempNode = tempNode->next;
			iCounter++;
		}

		//We have found the Node at the desired index
		return tempNode->data;
	}

	/** Returns the number of nodes in the linked list */
	virtual int size() const {
		if (head != NULL) {
			//The list is not empty, it has at least its header
			int iNumOfNodes = 1;
			Node* tempNode = head;

			while (tempNode->next != NULL) {
				iNumOfNodes++;
				tempNode = tempNode->next;
			}
			return iNumOfNodes; //We have searched through all of the nodes
								//in our list, so return the sum.
		}
		else {
			return 0;
		}
	}

	/**Finds out if the value already exists in the linked list. Returns true if it does exist alread**/
	bool find(T value) {
		Node* tempPointer = head;

		while (tempPointer != NULL) {//Search until the very ending node
			if (tempPointer->data == value) {
				return true;
			}
			else {
				tempPointer = tempPointer->next;
			}
		}
		return false; //The searched for pointer does not exist in the list.
	}

	/**Returns a string of all of the data from the linked list**/
	std::string printList() {
		std::ostringstream oss;
		
		Node* tempNode = head;

		while (tempNode != NULL) {
			//if statement for some formatting stuff
			if (tempNode->next != NULL) {
				oss << tempNode->data << " ";
			}
			else {
				oss << tempNode->data;
			}
			tempNode = tempNode->next;
		}

		return oss.str();
	}
};
#endif	/* LINKED_LIST_H */