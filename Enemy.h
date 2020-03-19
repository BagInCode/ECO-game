#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <algorithm>

#include "Weapon.h"

#include "Constants.db"

using namespace std;
using namespace sf;

class Enemy
{
	double positionX;
	double positionY;

	double angleMoving;
	double angleWathcing;

	pair < double, double > previousPosition;
	
	Weapon myWeapon;

	int healthPoints;

	double spriteLength;
	double spriteHigh;
public:

	void setAngleMoving(double _angleMoving);

	Weapon* getWeaponPointer();
	pair < double, double > getSize();
	void getDamage(int damage);
	pair < double, double > getPreviousPosition();

	int getHP();
	void setHP(int newHP);

	void setAngleWatching(double angle);
	double getAngleWatching();
	void calculateAngleWatching(Player & player);

	void setPosition(double newX, double newY);
	pair < double, double > getPosition();

	void move(double timer, double speed);
	void doAction(double timer);
	void create(double _positionX, double _positionY, Weapon weapon);
	bool isDead();

	Enemy();
	~Enemy();
};

