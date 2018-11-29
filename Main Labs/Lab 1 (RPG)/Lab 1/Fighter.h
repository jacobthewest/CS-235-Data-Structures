#ifndef FIGHTER_HPP_
#define FIGHTER_HPP_

#include "FighterInterface.h"
#include <sstream>

class Fighter : public FighterInterface {
public:
	Fighter() {}
	virtual ~Fighter() {}
	Fighter(std::string sName, int iMaxHitPoints, int iStrength, int iSpeed, int iMagic);
	std::string getName() const;
	virtual int getMaximumHP() const;
	virtual int getCurrentHP() const;
	virtual int getStrength() const;
	virtual int getSpeed() const;
	virtual int getMagic() const;
	virtual int getDamage() = 0;
	virtual void takeDamage(int damage);
	virtual void reset() = 0;
	virtual void regenerate() = 0;
	virtual bool useAbility() = 0;
	virtual std::string toString() = 0;
protected:
	std::string m_name;
	int m_currentHitPoints;
	int m_maximumHitPoints;
	int m_strength;
	int m_speed;
	int m_magic;
};

#endif /*FIGHTER_HPP_ */