#ifndef CLERIC_HPP_
#define CLERIC_HPP_

#include "Fighter.h"

class Cleric : public Fighter {
public:
	virtual ~Cleric() {}
	Cleric(std::string sName, int iMaxHitPoints, int iStrength, int iSpeed, int iMagic);
	virtual std::string toString();
	virtual int getDamage();
	virtual void reset();
	virtual bool useAbility();
	virtual void regenerate();
protected:
private:
	int CLERIC_MANA_MULTIPLIER = 5;
	int m_maximumMana = CLERIC_MANA_MULTIPLIER * m_magic;
	int m_currentMana;
};

#endif /*CLERIC_HPP_ */