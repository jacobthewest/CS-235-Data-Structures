#ifndef ROBOT_HPP_
#define ROBOT_HPP_

#include "Fighter.h"
#include <cmath>

class Robot : public Fighter {
public:
	virtual ~Robot() {}
	Robot(std::string sName, int iMaxHitPoints, int iStrength, int iSpeed, int iMagic);
	virtual std::string toString();
	virtual int getDamage();
	virtual void reset();
	virtual bool useAbility();
	virtual void regenerate();
protected:
private:	
	int ROBOT_ENERGY_MULTIPLIER = 2;
	int m_maximumEnergy;
	int m_currentEnergy;
	int m_bonusDamage;
};

#endif /*ROBOT_HPP_ */