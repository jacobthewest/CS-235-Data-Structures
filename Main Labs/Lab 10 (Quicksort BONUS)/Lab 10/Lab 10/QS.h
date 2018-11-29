/**************
Jacob West
LAB 10
***************/

#ifndef QS_H
#define QS_H

#include "QSInterface.h"

#include <sstream>
#include <array>

template<typename T>
class QS : public QSInterface<T> {
private:
	size_t m_capacity;
	T* arrayToSort;
	size_t numElements;
	size_t startingSizeOfArray;
public:
	QS() {}
	~QS() {}

	/** Dynamically allocate an initial array to the QuickSort class. */
	virtual bool createArray(size_t capacity) {
		if (arrayToSort != NULL) {
			//The array already exists so we need to delete it and then remake it.
			clear();
		}
			
		//Set capacity;
		this->m_capacity = capacity;
		this->startingSizeOfArray = capacity;
		arrayToSort = new T[capacity];

		//Set all values to 666
		for (size_t i = 0; i < m_capacity; i++) {
			arrayToSort[i] = 666;
		}
		return true;
	}

	/** Add an element to the QuickSort array. Dynamically grow array as needed. */
	virtual bool addElement(T element) {
		//Reallocate memory if we need to
		if (numElements == m_capacity) {
			reallocate();
		}

		//Insert into the array
		for (size_t i = 0; i < m_capacity; i++) {	
			if (arrayToSort[i] == 666) {
				arrayToSort[i] = element;
				numElements++;
				return true; //T'was inserted
			}
		}
		return false; //T'wasn't inserted
	}

	/** Sort the elements of a QuickSort subarray using median and partition functions. */
	virtual bool sort(size_t left, size_t right) {
		return true;
	}

	/** Sort all elements of the QuickSort array using median and partition functions. */
	virtual bool sortAll() {
		return true;
	}

	/** Removes all items from the QuickSort array. */
	virtual bool clear() {
		numElements = 0;
		//This could potentially cause problems for me in the future...
			//But I am going to delete the array and then create a new one.
		delete[] arrayToSort;
		arrayToSort = nullptr;
		//We are always going to return true, which is bad, but it is going to work haha.
		if (arrayToSort == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	/** Return size of the QuickSort array. */
	virtual size_t capacity() const {
		return this->m_capacity;
	}

	/** Return number of elements in the QuickSort array. */
	virtual size_t size() const {
		return numElements;
	}

	/** The median of three pivot selection has two parts:
	1) Calculates the middle index by averaging the given left and right indices:
	middle = (left + right)/2
	2) Then bubble-sorts the values at the left, middle, and right indices.

	After this method is called, data[left] <= data[middle] <= data[right].

	@param left - the left boundary for the subarray from which to find a pivot
	@param right - the right + 1 boundary for the subarray from which to find a pivot
	@return the index of the pivot (middle index).
	Return -1 if	1) the array is empty,
	2) if either of the given integers is out of bounds,
	3) or if the left index is not less than the right index.
	*/
	virtual int medianOfThree(size_t left, size_t right) {
		size_t middleIndex = (left + right) / 2; //Calculte the middle index

		//Check for errors. If they exist return an error number (-1)
		if (checkMedianOfThree(left, middleIndex, right) == -1) {
			return -1;
		}
		else {
			bubbleSort(left, middleIndex, right);	
			return middleIndex;
		}			
	}

	/** Partitions a subarray around a pivot value selected according
	to median-of-three pivot selection. Because there are multiple ways
	to partition a list, follow the algorithm on page 611.

	The values which are smaller than the pivot should be placed to the left of the pivot;
	the values which are larger than the pivot should be placed to the right of the pivot.

	@param left - left index for the subarray to partition.
	@param right - right index + 1 for the subarray to partition.
	@param pivotIndex - index of the pivot in the subarray.
	@return the pivot's ending index after the partition completes:
	Return -1 if	1) the array is empty,
	2) if any of the given indexes are out of bounds,
	3) if the left index is not less than the right index.
	*/
	virtual int partition(size_t left, size_t right, size_t pivotIndex) {
		string stringCheck;
		//left, middleIndex, right
		if (checkMedianOfThree(left, pivotIndex, right) == -1) {
			return -1;
		}

		//1--sort left, right, and pivotIndex
		bubbleSort(left, pivotIndex, right);
		stringCheck = toString();

		int pivotValue = arrayToSort[pivotIndex];

		//2---Move the median value to the first position (the pivot value) by exchanging 
		//arrayToSort[left] and arrayToSort[pivotIndex]
		int tempForSwitch;
		tempForSwitch = arrayToSort[left];
		arrayToSort[left] = arrayToSort[pivotIndex];
		arrayToSort[pivotIndex] = tempForSwitch;
		stringCheck = toString();

		size_t up;
		size_t down;

		//Initialize up to first + 1 and down to last - 1
		up = left + 1;
		down = right - 1;

		do {
			while (!(up == right - 1) && !(arrayToSort[up] > pivotValue)) {
				++up;
			}
			size_t checkUp = up;
			//Assert: up equals last -1 or arrayToSort[up] > table[first].
			while (!(arrayToSort[down] <= pivotValue) && !(down == left)) {
				--down;
			}
			size_t checkDown = down;
			//Assert: down equals first or arrayToSort[down] <= arrayToSort[left]
			if (up < down) { //if up is left of down
				//Exchange arrayToSort[up] and arrayToSort[down].
				tempForSwitch = arrayToSort[up];
				arrayToSort[up] = arrayToSort[down];
				arrayToSort[down] = tempForSwitch;
			}
		} while (up < down); //Repeat while up is left of down

		//Exchange arrayToSort[lefft] and arrayToSort[down] thus putting
		//the pivot value where it belongs
		//Return the position of pivot

		tempForSwitch = arrayToSort[left];
		arrayToSort[left] = arrayToSort[down];
		arrayToSort[down] = tempForSwitch;
		return down;
	}

	/** @return: comma delimited string representation of the array. */
	virtual std::string toString() const {
		std::ostringstream oss;
		bool bPrintEmpty = true;
		for (size_t i = 0; i < numElements; i++) {
			if (arrayToSort[i] != 666 && (i != (numElements - 1))) {
				oss << arrayToSort[i] << ",";
				bPrintEmpty = false;
			}
			else {
				oss << arrayToSort[i];
				bPrintEmpty = false;
			}
		}
		if (bPrintEmpty) {
			return "Empty";
		}
		else {
			return oss.str();
		}		
	}

	//Doubles the size of the array
	void reallocate() {
		size_t new_capacity = 2 * m_capacity;
		T* new_arrayToSort = new T[new_capacity];
		size_t j = 0;
		for (size_t i = 0; i < numElements; i++) {
			new_arrayToSort[i] = arrayToSort[j];
			j++;
		}
		this->m_capacity = new_capacity;
		//Put NULL in the rest of the values in the new_arrayToSort
		for (size_t i = numElements; i < new_capacity; i++) {
			new_arrayToSort[i] = 666;
		}
		std::swap(arrayToSort, new_arrayToSort);

		delete[] new_arrayToSort;
	}

	//Sets the starting size of the array
	bool setStartingSize(size_t number) {
		this->startingSizeOfArray = number;
	}
	//Return 1 if there are no errors with the passed in values
	/*Return - 1 if	1) the array is empty,
	2) if either of the given integers is out of bounds,
	3) or if the left index is not less than the right index.
	*/
	int checkMedianOfThree(size_t left, size_t middle, size_t right) {
		if (size() == 0) {
			return -1; //The array is empty.
		}
		else if (right > size()) {
			return -1; //The right index is out of bounds
		}
		else if (left > right) {
			return -1; //Left index is greater than the right index;
		}
		else{
			return 1;
		}
	}

	//Function to order left, middle Index and right index in the array
	void bubbleSort(size_t left, size_t middleIndex, size_t right) {
		int temp;

		if (right == size()) {
			right -= 1;
		}

		while (arrayToSort[middleIndex] > arrayToSort[right] || arrayToSort[left] > arrayToSort[middleIndex]) {
			if (arrayToSort[middleIndex] > arrayToSort[right]) { //Value at middle is > value at right
				temp = arrayToSort[middleIndex];
				arrayToSort[middleIndex] = arrayToSort[right];
				arrayToSort[right] = temp;
			}
			//Bubble sort through left, middle, and right to make sure that their values are in order
			if (arrayToSort[left] > arrayToSort[middleIndex]) { //Value at left is > value at middle
				temp = arrayToSort[left];
				arrayToSort[left] = arrayToSort[middleIndex];
				arrayToSort[middleIndex] = temp;
			}
		}
	}
};

#endif /*QS_H*/