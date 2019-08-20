/*
*
* created by @BagInCode
* for Eloped Crime Object Game
*
*/

#pragma once

#ifndef WEAPON_CLASS
#define WEAPON_CLASS

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <math.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <time.h>
#include <random>
#include <fstream>

#include "Bullet.h"
#include "Constants.db"

using namespace std;
using namespace sf;

class Weapon
{
	int maxAmmo;
	int currentAmmo;
	int damage;
	double accuracy;
	double delayBetweenShoots;
	double timer;
	double reloadTime;

public:
	Weapon();
	~Weapon();

	void setMaxAmmo(int newMaxAmmo);
	void setCurrentAmmo(int newCurrentAmmo);
	void setDamage(int newDamage);
	void setAccuracy(double newAccurasy);
	void setDelayBetweenShoots(double newDelayBetweenShoots);
	void setTimer(double newTimer);
	void setReloadTime(double newReloadTime);

	int getMaxAmmo();
	int getCurrentAmmo();
	int getDamage();
	double getAccurasy();
	double getDelayBetweenShoots();
	double getTimer();
	double getReloadTime();

	void create(int weaponType);
	void increaseTimer(double delt);
	double calcAccuracy();
	
};

#endif
