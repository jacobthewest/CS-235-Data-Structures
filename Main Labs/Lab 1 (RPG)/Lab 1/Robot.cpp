#include "Robot.h"


//Constructors
Robot::Robot(std::string sName, int iMaxHitPoints, int iStrength, int iSpeed, int iMagic) {
	this->m_name = sName;
	this->m_maximumHitPoints = iMaxHitPoints;
	this->m_currentHitPoints = m_maximumHitPoints;
	this->m_strength = iStrength;
	this->m_speed = iSpeed;
	this->m_magic = iMagic;
	this->m_maximumEnergy = 2 * m_magic;
	this->m_currentEnergy = m_maximumEnergy;
	this->m_bonusDamage = 0;
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
std::string Robot::toString() {
	std::ostringstream out;
	out << m_name << " " << m_currentHitPoints << " " << m_maximumHitPoints << " " <<
		m_strength << " " << m_speed << " " << m_magic;
	return out.str();
}
/*
*	getDamage()
*
*	Returns the amount of damage a fighter will deal.
*
*	Robot:
*	This value is equal to the Robot's strength plus any additional damage added for having just used its special ability.
*/
int Robot::getDamage() {
	int iDamage = m_strength + m_bonusDamage;
	return iDamage;
}
/*
*	reset()
*
*	Restores a fighter's current hit points to its maximum hit points.
*
*	Robot:
*	Also restores a Robot's current energy to its maximum value (which is 2 times its magic).
*	Also resets a Robot's bonus damage (calculated when a Robot uses its ability) to 0.
*/
void Robot::reset() {
	m_currentHitPoints = m_maximumHitPoints;
	m_currentEnergy = m_maximumEnergy;
	m_bonusDamage = 0;
}
/*
*	useAbility()
*
*	Attempts to perform a special ability based on the type of fighter.  The
*	fighter will attempt to use this special ability just prior to attacking
*	every turn.
*
*	Robot: Shockwave Punch
*	Adds bonus damage to the Robot's next attack (and only its next attack) equal to (strength  * ((current_energy/maximum_energy)^4)).
*	Can only be used if the Robot has at least [ROBOT_ABILITY_COST] energy.
*	Decreases the Robot's current energy by [ROBOT_ABILITY_COST] (after calculating the additional damage) when used.
*		Examples:
*		strength=20, current_energy=20, maximum_energy=20		=> bonus_damage=20
*		strength=20, current_energy=15, maximum_energy=20		=> bonus_damage=6
*		strength=20, current_energy=10, maximum_energy=20		=> bonus_damage=1
*		strength=20, current_energy=5,  maximum_energy=20		=> bonus_damage=0
*
*	Robot Note:
*	The bonus damage formula should be computed using double arithmetic, and only
*	the final result should be cast into an integer.
*	
*	Return true if the ability was used; false otherwise.
*/
bool Robot::useAbility()  {
	m_bonusDamage = 0;
	int POWER_TO_RAISE_FOR_BONUS_DAMAGE = 4;
	double dCurrentEnergyAsDouble = m_currentEnergy;
	double dFraction = dCurrentEnergyAsDouble / m_maximumEnergy; //just need one double to convert the int to a double

	if (m_currentEnergy >= ROBOT_ABILITY_COST) {
		m_bonusDamage = static_cast<int>(m_strength * (std::pow(dFraction, POWER_TO_RAISE_FOR_BONUS_DAMAGE)));
		m_currentEnergy -= ROBOT_ABILITY_COST;
		return true; //useAbility was successful
	}
	else {
		return false; //was not used.
	}
}

/*
*	regenerate()
*
*	Increases the fighter's current hit points by an amount equal to one sixth of
*	the fighter's strength.  This method must increase the fighter's current hit
*	points by at least one.  Do not allow the current hit points to exceed the
*	maximum hit points.
*/
void Robot::regenerate() {
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