#include "Fighter.h"

//Constructors
Fighter::Fighter(std::string sName, int iMaxHitPoints, int iStrength, int iSpeed, int iMagic) {
	this->m_name = sName;
	this->m_maximumHitPoints = iMaxHitPoints;
	this->m_currentHitPoints = m_maximumHitPoints;
	this->m_strength = iStrength;
	this->m_speed = iSpeed;
	this->m_magic = iMagic;
}



//--------Getters--------//
std::string Fighter::getName() const {
	return this->m_name;
}
int Fighter::getMaximumHP() const {
	return this->m_maximumHitPoints;
}
/*
*	getCurrentHP()
*
*	Returns the current hit points of this fighter.
*/
int Fighter::getCurrentHP() const {
	return this->m_currentHitPoints;
}

int Fighter::getStrength() const {
	return this->m_strength;
}
int Fighter::getSpeed() const {
	return this->m_speed;
}
int Fighter::getMagic() const {
	return this->m_magic;
}

//--------Other Functions--------//
/*
*	takeDamage(int)
*
*	Reduces the fighter's current hit points by an amount equal to the given
*	damage minus one fourth of the fighter's speed.  This method must reduce
*	the fighter's current hit points by at least one.  It is acceptable for
*	this method to give the fighter negative current hit points.
*
*	Examples:
*		damage=10, speed=7		=> damage_taken=9
*		damage=10, speed=9		=> damage_taken=8
*		damage=10, speed=50		=> damage_taken=1
*/
void Fighter::takeDamage(int damage) {
	int damageTaken = (damage - static_cast<int>(m_speed * .25));
	if (damageTaken < 1) {
		//If they are so fast that the damge taken is less than 1, force it to be 1.
		damageTaken = 1;
	}
	m_currentHitPoints -= damageTaken; //subtracts damageTaken from m_currentHitPoints
}
