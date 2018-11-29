/**********************
Jacob West
Lab 07
CS 235 Section 1
jacobthewest@gmail.com
**********************/

#ifndef BST_H
#define BST_H

#include "BSTInterface.h"

#include <fstream>
#include <sstream>

template<typename T>
class BST : public BSTInterface<T> {
private:
	struct Node	{
		T data_;
		Node* left_;
		Node* right_;
		Node(T d) : data_(d), left_(NULL), right_(NULL) {}
	};
	Node* root_;
public:
	BST() { this->root_ = NULL; }
	~BST() { clearTree(); }

	/** Return true if node added to BST, else false */
	virtual bool addNode(const T& data) { return insert(root_, data); }

	/** Return true if node removed from BST, else false */
	virtual bool removeNode(const T& data) { return remove(root_, data); }

	/** Return true if BST cleared of all nodes, else false */
	virtual bool clearTree() { return deleteTree(root_); }

	/**Return true if the null was successfully removed from the tree. Is called recursively. **/
	bool remove(Node*& node, const T& data) {
		if (node == NULL) { //if node is NULL, return false
			return false;
		}
		else if (data < node->data_) { //if data < node->data, return remove(node->left, data)
			return remove(node->left_, data);
		}
		else if (data > node->data_) { //if data > node->data, return remove(node->right, data)
			return remove(node->right_, data);
		}
		else { //Found item
			Node* old_root = node;
			if (node->left_ == NULL) {
				node = node->right_; //Grandpa node now points to grandson
			}
			else if (node->right_ == NULL) {
				node = node->left_; //Grandpa node now points to grandson
			}
			else { 
				replace_parent(old_root, old_root->left_);
			}
			delete old_root;
			return true;
		}	
	}
	/**Function that replaces the parent node. Useful when the current node is a leaf node **/
	void replace_parent(Node*& old_root, Node*& root) {
		if (root->right_ != NULL) {
			replace_parent(old_root, root->right_);
		}
		else { //The node we want to delete is a leaf node;
			old_root->data_ = root->data_;
			old_root = root;
			root = root->left_;
		}
	}
	/**Return true if the null was successfully added to the tree. Is called recursively. Prevents duplicates **/
	bool insert(Node*& node, const T& data) {
		//If node is null
		if (node == NULL) { //Does this need to be nullptr?
 			node = new Node(data);
			return true; //Node successfully inserted;
		}			
		else {
			if (data < node->data_) {
				return insert(node->left_, data); //Insert left if data is less than
			}
			else if (data > node->data_) {
				return insert(node->right_, data); //Insert right if data is less than
			}
			else {
				return false;
			}
		}
	}
	
	/** This function deletes all pointers in the tree to free up memory to avoid leaks. Is called recursively **/
	bool deleteTree(Node*& root) {
		while (root != NULL) {
			remove(root, root->data_);
		}
		return true;
	}

	/** Output nodes at a given level */
	bool outLevel(Node* root, int level, std::stringstream& out) const {
		if (root == NULL) {
			return false;
		}
		if (level == 0)	{
			out << " " << root->data_;
			if ((root->left_ != NULL) || (root->right_ != NULL)) {
				return true;
			}
			else {
				return false;
			}
		}
		if ((level == 1) && !root->left_ && root->right_) out << " _";
		bool left = outLevel(root->left_, level - 1, out);
		bool right = outLevel(root->right_, level - 1, out);
		if ((level == 1) && root->left_ && !root->right_) out << " _";
		return left || right;
	} // end outLevel()

	/** Return a level order traversal of a BST as a string */
	virtual string toString() const	{
		std::stringstream out;
		if (root_ == NULL) out << " Empty";
		else {
			int level = -1;
			do {
				out << std::endl << "  " << ++level << ":";
			} while (outLevel(root_, level, out));
		}
		return out.str();
	} // end toString()
};

#endif	// BST_H