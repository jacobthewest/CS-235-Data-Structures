#ifndef ARENA_HPP_
#define ARENA_HPP_

#include "ArenaInterface.h"
#include "Fighter.h"
#include "Archer.h"
#include "Cleric.h"
#include "Robot.h"
#include <sstream> //used for ostringstream

class Arena : public ArenaInterface {
public:
	~Arena();
	bool addFighter(std::string info); //If there is an "object has type qualifiers" error it is because of
		//using const in the .h and .cpp Arena files because the ArenaInterface.h file has addFighter as a pure virtual function.	
	bool removeFighter(std::string name);
	FighterInterface* getFighter(std::string name);
	int getSize() const;
	bool resetFighter(std::string sName);
	//bool checkForFailedInput(std::stringstream ss);
protected:
private:
	std::vector<Fighter*> vectorOfFighters;
};

#endif /*ARENA_HPP_*/