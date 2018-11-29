#ifndef ARCHER_HPP_
#define ARCHER_HPP_

#include "Fighter.h"

class Archer : public Fighter {
public:
	virtual ~Archer() {}
	Archer(std::string sName, int iMaxHitPoints, int iStrength, int iSpeed, int iMagic);
	virtual std::string toString();
	virtual int getDamage();
	virtual void reset();
	virtual bool useAbility();
	virtual void takeDamage(int damage);
	virtual void regenerate();
protected:
private:
	int m_currentSpeed;
};

#endif /*ARCHER_HPP_ */