#include "Weapon.h"



Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}


void Weapon::setMaxAmmo(int newMaxAmmo)
{
	/*
	* funciton of setting max ammo
	*
	* @param newMaxAmmo - new max ammo
	*/

	maxAmmo = newMaxAmmo;

	return;
}


void Weapon::setCurrentAmmo(int newCurrentAmmo)
{
	/*
	* function of setting new current ammo
	*
	* @param newCurrentAmmo - new current ammo
	*/

	currentAmmo = newCurrentAmmo;

	return;
}

void Weapon::setDamage(int newDamage)
{
	/*
	* function of setting new damage
	*
	* @param newDamage - new damage
	*/

	damage = newDamage;

	return;
}

void Weapon::setAccuracy(double newAccurasy)
{
	/*
	* function of setting new accurasy
	*
	* @param newAccurasy - new accurasy
	*/

	accuracy = newAccurasy;

	return;
}

void Weapon::setDelayBetweenShoots(double newDelayBetweenShoots)
{
	/*
	* function of setting deley between shoots
	*
	* @param newDelayBetweenShoots - new delau between shoots
	*/

	delayBetweenShoots = newDelayBetweenShoots;

	return;
}

void Weapon::setTimer(double newTimer)
{
	/*
	* function of setting timer
	*
	* @param newTimer - new timer value
	*/

	timer = newTimer;

	return;
}

void Weapon::setReloadTime(double newReloadTime)
{
	/*
	* function of setting reload time
	*
	* @param newReloadTime - new reload time
	*/

	reloadTime = newReloadTime;

	return;
}

int Weapon::getMaxAmmo()
{
	/*
	* function of getting max ammo
	*
	* @return max ammo
	*/

	return maxAmmo;
}

int Weapon::getCurrentAmmo()
{
	/*
	* function of getting current ammo
	*
	* @return current ammo
	*/

	return currentAmmo;
}


int Weapon::getDamage()
{
	/*
	* functionf of getting weapon damage
	*
	* @return weapon damage
	*/

	return damage;
}

double Weapon::getAccurasy()
{
	/*
	* function of getting weapon accurasy
	*
	* @return weapon accurasy
	*/

	return accuracy;
}

double Weapon::getDelayBetweenShoots()
{
	/*
	* function of getting delay between shoots
	*
	* @return delay between shoots
	*/

	return delayBetweenShoots;
}

double Weapon::getTimer()
{
	/*
	* function of getting timer
	*
	* @return timer
	*/

	return timer;
}

double Weapon::getReloadTime()
{
	/*
	* function of getting reload time
	*
	* @return reload time
	*/

	return reloadTime;
}

void Weapon::create(int weaponType)
{
	/*
	* function of initialization weapon object
	*
	* @param weaponType - type of weapon
	*/

	// set maximal ammo
	maxAmmo = WEAPON_MAX_AMMO[weaponType];

	// set current ammo equal to maximal ammo
	currentAmmo = maxAmmo;

	// set weapon damage
	damage = WEAPON_DAMAGE[weaponType];

	// set weapon accurasy, convert from degrees to radians
	accuracy = WEAPON_ACCURACY[weaponType] * PI / 180.;

	// set delay between shoots
	delayBetweenShoots = WEAPON_RELOAD_BULLET[weaponType];

	// set reload time
	reloadTime = WEAPON_RELOAD_AMMO[weaponType];

	// set timer equal to zero
	timer = 0;

	return;
}

void Weapon::increaseTimer(double delt)
{
	/*
	* function of increasing timer
	*
	* @param delt - how much have to add
	*/

	timer += delt;

	return;
}

double Weapon::calcAccuracy()
{
	/*
	* function of returning random value in [- weapon accurasy .. + weapon accurasy]
	*
	* @return result of random
	*/

	// calc value in [-100 .. +100]
	double accuracyValue = (rand() % 201)-100;

	// convert it to [-1 .. +1]
	accuracyValue = accuracyValue / 100.;

	// calc final value and return it
	return accuracyValue * accuracy;
}