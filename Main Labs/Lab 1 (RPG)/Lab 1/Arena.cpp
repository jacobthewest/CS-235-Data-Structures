#include "Arena.h"

Arena::~Arena() {
	for (unsigned int i = 0; i < vectorOfFighters.size(); i++) {
		delete vectorOfFighters.at(i);
	}
}

/*
*	addFighter(string)
*
*	Adds a new fighter to the collection of fighters in the arena. Do not allow
*	duplicate names.  Reject any string that does not adhere to the format
*	outlined in the lab specs.
*
*	Return true if a new fighter was added; false otherwise.
*/
bool Arena::addFighter(std::string info) {
	bool bFighterAdded = true;
	std::string sFighterName;
	char cFighterClass;
	int iMaxHitPoints;
	int iStrength;
	int iSpeed;
	int iMagic;	

	//FIXME: I need to check for invalid string input.

	std::stringstream ss;
	ss << info; //the passed in stream is now in our stringstream
	ss >> sFighterName; //first name is stored from our stringstream
	if (ss.fail()) {
		ss.clear();
		return false;
	}
	ss >> cFighterClass;
	if (ss.fail()) {
		ss.clear();
		return false;
	}
	ss >> iMaxHitPoints;
	if (ss.fail()) {
		ss.clear();
		return false;
	}
	ss >> iStrength;
	if (ss.fail()) {
		ss.clear();
		return false;
	}
	ss >> iSpeed;
	if (ss.fail()) {
		ss.clear();
		return false;
	}
	ss >> iMagic;
	if (ss.fail()) {
		ss.clear();
		return false;
	}
	if (ss.rdbuf()->in_avail() != 0) {
		//The rest of the buffer IS NOT empty
		return false;
	}

	for (unsigned int i = 0; i < vectorOfFighters.size(); i++) {
		if (vectorOfFighters.at(i)->getName() == sFighterName) {
			bFighterAdded = false;	
			return bFighterAdded;
		}
	}
	//----------We did not find a matching name, so we have the clear to add the fighter----------//

	//Add a pointer to our vectorOfFighters for the new fighter
	if (cFighterClass == 'A') {
		vectorOfFighters.push_back(new Archer(sFighterName, iMaxHitPoints, iStrength, iSpeed, iMagic));
	}
	else if (cFighterClass == 'C') {
		vectorOfFighters.push_back(new Cleric(sFighterName, iMaxHitPoints, iStrength, iSpeed, iMagic));
	}
	else if (cFighterClass == 'R') {
		vectorOfFighters.push_back(new Robot(sFighterName, iMaxHitPoints, iStrength, iSpeed, iMagic));
	}
	else {
		return false; //Fighet was not added because we did not recognize its fighting class
	}	
	return bFighterAdded;
}
/*
*	removeFighter(string)
*
*	Removes the fighter whose name is equal to the given name.  Does nothing if
*	no fighter is found with the given name.
*
*	Return true if a fighter is removed; false otherwise.
*/
bool Arena::removeFighter(std::string name) {
	bool bFighterRemoved = false;

	for (unsigned int i = 0; i < vectorOfFighters.size(); i++) {
		if (vectorOfFighters.at(i)->getName() == name) {
			bFighterRemoved = true;
				
			//Delete the fighter from allocated memory
			delete vectorOfFighters.at(i);

			//Delete the pointer to the vector from our vector of fighter pointers
			vectorOfFighters.erase(vectorOfFighters.begin() + i);

			return bFighterRemoved;
		}
	}

	//We did not find the fighter in the vector...return false
	return bFighterRemoved;
}
/*
*	getFighter(string)
*
*	Returns the memory address of a fighter whose name is equal to the given
*	name.  Returns NULL if no fighter is found with the given name.
*
*	Return a memory address if a fighter is found; NULL otherwise.
*/
FighterInterface* Arena::getFighter(std::string name) {
	for (unsigned int i = 0; i < vectorOfFighters.size(); i++) {
		if (vectorOfFighters.at(i)->getName() == name) {
			return vectorOfFighters.at(i); 
		}
	}
	//We did not find a fighter by that name...
	return NULL;
}
/*
*	getSize()
*
*	Returns the number of fighters in the arena.
*
*	Return a non-negative integer.
*/
int Arena::getSize() const {
	//returns the number of fighters in our vector of fighters.
	return vectorOfFighters.size();
}
bool Arena::resetFighter(std::string sName) {
	bool bResetWasSuccessful = false;

	for (unsigned int i = 0; i < vectorOfFighters.size(); i++) {
		if (vectorOfFighters.at(i)->getName() == sName) {
			vectorOfFighters.at(i)->reset();
			if (vectorOfFighters.at(i)->getCurrentHP() == vectorOfFighters.at(i)->getMaximumHP()) {
				bResetWasSuccessful = false;
				return bResetWasSuccessful;
			}
		}
	}
	return bResetWasSuccessful; //Will be false unless the name searched for was found
		//and the reset made the fighter's current HP equal to the maximum HP
}