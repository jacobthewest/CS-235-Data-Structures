#include "Cleric.h"

//Constructors
Cleric::Cleric(std::string sName, int iMaxHitPoints, int iStrength, int iSpeed, int iMagic) {
	this->m_name = sName;
	this->m_maximumHitPoints = iMaxHitPoints;
	this->m_currentHitPoints = m_maximumHitPoints;
	this->m_strength = iStrength;
	this->m_speed = iSpeed;
	this->m_magic = iMagic;
	this->m_currentMana = m_maximumMana;
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
std::string Cleric::toString() {
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
*	Cleric:
*	This value is equal to the Cleric's magic.
*/
int Cleric::getDamage() {
	int iDamage = m_magic;
	return iDamage;
}
/*
*	reset()
*
*	Restores a fighter's current hit points to its maximum hit points.
*
*	Cleric:
*	Also restores a Cleric's current mana to its maximum value (which is 5 times its magic).
*/
void Cleric::reset() {
	m_currentHitPoints = m_maximumHitPoints;
	m_currentMana = m_maximumMana;
}
/*
*	regenerate()
*
*	calls Fighter::regenerate() and Increases the fighter's current hit points by 
*	an amount equal to one sixth of	the fighter's strength.  This method must increase 
*	the fighter's current hitpoints by at least one.  Do not allow the current hit 
*	points to exceed the maximum hit points.
*
*	Cleric:
*	Also increases a Cleric's current mana by an amount equal to one fifth of the
*	Cleric's magic.  This method must increase the Cleric's current mana by at
*	least one.  Do not allow the current mana to exceed the maximum mana (again, 5 times its magic).
*/
void Cleric::regenerate() {
	
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

	double MANA_INCREASE_AMOUNT = m_magic * (static_cast<double>(1) / 5); 
	int iManaIncrease = static_cast<int>(m_magic * MANA_INCREASE_AMOUNT);

	//increase the current mana by at least one if it won't be increase by more than 1
	if (iManaIncrease < 1) {
		iManaIncrease = 1;
	}

	//make sure the current mana can't be higher than the maximum mana
	if ((m_currentMana + iManaIncrease) > m_maximumMana) {
		m_currentMana = m_maximumMana;
	}
	//Normal case, just add mana.
	else {
		m_currentMana += iManaIncrease;
	}
}
/*
*	useAbility()
*
*	Attempts to perform a special ability based on the type of fighter.  The
*	fighter will attempt to use this special ability just prior to attacking
*	every turn.

*	Cleric: Healing Light
*	Increases the Cleric's current hit points by an amount equal to one third of its magic.
*	Can only be used if the Cleric has at least [CLERIC_ABILITY_COST] mana.
*	Will be used even if the Cleric's current HP is equal to their maximum HP.
*	Decreases the Cleric's current mana by [CLERIC_ABILITY_COST] when used.
*
*	Cleric Note:
*	This ability, when successful, must increase the Cleric's current hit points
*	by at least one, unless doing so would given the Cleric more hit points than its maximum hit points.
*	Do not allow the current hit points to exceed the maximum hit points.
*
*	Return true if the ability was used; false otherwise.
*/
bool Cleric::useAbility() {
	double PORTION_OF_MAGIC_FOR_THE_CURRENT_HP_INCREASE = (static_cast<double>(1) / 3);
	int iIncreaseToCurrentHP = static_cast<int>(m_magic * PORTION_OF_MAGIC_FOR_THE_CURRENT_HP_INCREASE);

	if (m_currentMana >= CLERIC_ABILITY_COST) {
		if (iIncreaseToCurrentHP < 1) {
			//Give them at least 1 extra currentHP point
			m_currentHitPoints += 1;
		}
		else if ((m_currentHitPoints + iIncreaseToCurrentHP) > m_maximumHitPoints) {
			m_currentHitPoints = m_maximumHitPoints;
		}
		else {
			//just add the increase to their current HP
			m_currentHitPoints += iIncreaseToCurrentHP;
		}
		m_currentMana -= CLERIC_ABILITY_COST;
		return true; //We successfully used the ability
	}
	else {
		return false; //No change was made
	}
}