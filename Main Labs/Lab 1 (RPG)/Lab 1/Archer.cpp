#include "Archer.h"

//Constructors
Archer::Archer(std::string sName, int iMaxHitPoints, int iStrength, int iSpeed, int iMagic) {
	this->m_name = sName;
	this->m_maximumHitPoints = iMaxHitPoints;
	this->m_currentHitPoints = m_maximumHitPoints;
	this->m_strength = iStrength;
	this->m_speed = iSpeed;
	this->m_magic = iMagic;
	this->m_currentSpeed = m_speed;
}
/*
*	toString()
*
*	Prints out fighters information in a formatted manner.  The output of this method is independent
*	of figher type and should be of the following format:
*
*	<name> <current HP> <maximum HP> <strength> <speed> <magic>
*
*/
std::string Archer::toString() {
	std::ostringstream out;
	out << m_name << " " << m_currentHitPoints << " " << m_maximumHitPoints << " " <<
		m_strength << " " << m_currentSpeed << " " << m_magic;
	return out.str();
}
/*
*	getDamage()
*
*	Returns the amount of damage a fighter will deal.
*
*	Archer:
*	This value is equal to the Archer's speed.
*/
int Archer::getDamage() {
	int iDamage = m_currentSpeed;
	return iDamage;
}
/*
*	reset()
*
*	Restores a fighter's current hit points to its maximum hit points.
*
*	Archer:
*	Also resets an Archer's current speed to its original value.
*/
void Archer::reset() {
	m_currentHitPoints = m_maximumHitPoints;
	m_currentSpeed = m_speed;
}
/*
*	useAbility()
*
*	Attempts to perform a special ability based on the type of fighter.  The
*	fighter will attempt to use this special ability just prior to attacking
*	every turn.
*
*	Archer: Quickstep
*	Increases the Archer's speed by one point each time the ability is used.
*	This bonus lasts until the reset() method is used.
*	This ability always works; there is no maximum bonus speed.
*
*	Return true if the ability was used; false otherwise.
*/
bool Archer::useAbility() {
	int iOriginalCurrentSpeed = m_currentSpeed;
	m_currentSpeed += 1;

	if (m_currentSpeed != iOriginalCurrentSpeed) {
		return true;
	}
	else {
		return false;
	}
}
/*
	Recieves the damageTaken and applies it to the fighter
*/
void Archer::takeDamage(int damage) {
	int damageTaken = (damage - static_cast<int>(m_currentSpeed * .25));
	if (damageTaken < 1) {
		//If they are so fast that the damge taken is less than 1, force it to be 1.
		damageTaken = 1;
	}
	m_currentHitPoints -= damageTaken; //subtracts damageTaken from m_currentHitPoints
}
/*
*	regenerate()
*
*	Increases the fighter's current hit points by an amount equal to one sixth of
*	the fighter's strength.  This method must increase the fighter's current hit
*	points by at least one.  Do not allow the current hit points to exceed the
*	maximum hit points.
*/
void Archer::regenerate() {
	double CURRENT_HIT_POINTS_INCREASE_AMOUNT = (static_cast<double>(1) / 6);
	int iHPIncrease = static_cast<int>(m_strength * CURRENT_HIT_POINTS_INCREASE_AMOUNT);

	if (iHPIncrease < 1) {
		iHPIncrease = 1;
	}

	if ((iHPIncrease + m_currentHitPoints) > m_maximumHitPoints) {
		m_currentHitPoints = m_maximumHitPoints;
	}
	//Normal case with no exceptions
	else {
		m_currentHitPoints += iHPIncrease;
	}
}