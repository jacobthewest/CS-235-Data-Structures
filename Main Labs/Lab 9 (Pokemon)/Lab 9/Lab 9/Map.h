/**********************
Jacob West
Lab 09
CS 235 Section 1
jacobthewest@gmail.com
**********************/

#include "MapInterface.h"
#include "Set.h"

#ifndef MAP_H
#define MAP_Hf

// Generic template for map<key,value>
template<typename K, typename V>
class Map : public MapInterface<K, V> {
private:
	std::pair<K, V>* values;
public:
	static const int HashTableSize = 31;
	static const int BonusHashTableSize = 7;
	
	/** Construct an empty map */
	Map() {
		values = new std::pair<K, V>[HashTableSize];
	};
	~Map() { 
		delete[] values;
	};

	/** Read/write index access operator.
	If the key is not found, an entry is made for it.
	@return: Read and write access to the value mapped to the provided key. */
	virtual V& operator[](const K& key) {
		size_t index = hash(key);
		values[index].first = key;
		V& returnMe = values[index].second;
		return returnMe;
	}

	/** @return: the number of elements removed from the Map. */
	virtual size_t erase(const K& key) {
		return 90;
	}

	/** @return: number of Key-Value pairs stored in the Map. */
	virtual size_t size() const {
		return 0;
	}

	/** Removes all items from the Map. */
	virtual void clear() {
		//Do nothing;
	}

	/** @return: maximum number of Key-Value pairs that the Map can hold. */
	virtual size_t max_size() const {
		return HashTableSize;
	}

	/** @return: string representation of Key-Value pairs in Map. */
	virtual std::string toString() const {
		std::ostringstream oss;
		for (int i = 0; i < HashTableSize; i++) {
			if (values[i].first != "") {
				oss << values[i].first << ": " << values[i].second << std::endl;
			}
		}
		return oss.str();
	}

	//Creates a hash index for the word. Stores the word in the array//
	int hash(const K& word) {
		size_t iTotalCount = 0;
		for (size_t i = 0; i < word.length(); i++) {
			iTotalCount += word[i];
		}
		size_t index = iTotalCount % HashTableSize;
		while (values[index % HashTableSize].first != "" && values[index % HashTableSize].first != word) {
			index++;
		}
		return index % HashTableSize;
	}
}; // End of Map

template<>
class Map<string, Set<string>> : public MapInterface<string, Set<string>> {
private:
	std::pair<string, Set<string>>* values;
public:
	static const int HashTableSize = 31;
	static const int BonusHashTableSize = 7;

	/** Construct an empty map */
	Map() {
		values = new std::pair<string, Set<string>>[HashTableSize];
	};
	~Map() {
		for (int i = 0; i < HashTableSize; i++) {
			if (values[i].first != "") {
				values[i].second.clear();
			}
		}
		delete[] values;
	};

	/** Removes all items from the Map. */
	virtual void clear() {
		//Do nothing;
	}

	/** Read/write index access operator.
	If the key is not found, an entry is made for it.
	@return: Read and write access to the value mapped to the provided key. */
	virtual Set<string>& operator[](const string& key) {
		size_t index = hash(key);
		values[index].first = key;
		Set<string>& returnMe = values[index].second;
		return returnMe;
	}

	/** @return: the number of elements removed from the Map. */
	virtual size_t erase(const string& key) {
		return 666; //:)
	}

	/** @return: number of Key-Value pairs stored in the Map. */
	virtual size_t size() const {
		return 0;
	}

	/** @return: maximum number of Key-Value pairs that the Map can hold. */
	virtual size_t max_size() const {
		return HashTableSize;
	}

	/** @return: string representation of Key-Value pairs in Map. */
	virtual std::string toString() const {
		std::ostringstream oss;
		for (int i = 0; i < HashTableSize; i++) {
			if (values[i].first != "") {
				oss << values[i].first << ": " << values[i].second.toStringLegit() << std::endl;
			}
		}
		return oss.str();
	}

	//Creates a hash index for the word. Stores the word in the array//
	int hash(const string& word) {
		size_t iTotalCount = 0;
		for (size_t i = 0; i < word.length(); i++) {
			iTotalCount += word[i];
		}
		size_t index = iTotalCount % HashTableSize;
		while (values[index % HashTableSize].first != "" && values[index % HashTableSize].first != word) {
			index++;
		}
		return index;
	}
};
#endif // MAP_H