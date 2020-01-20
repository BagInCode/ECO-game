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
	
	Weapon myWeapon;

	int healthPoints;

	double spriteLength;
	double spriteHigh;
public:

	void move(double timer, double speed);
	Weapon* getWeaponPointer();
	void calculateAngleWatching(Player & player);
	double getAngleWatching();
	void setAngleMoving(double _angleMoving);
	pair < double, double > getPosition();
	void doAction(double timer);
	pair < double, double > getSize();
	void setPosition(double newX, double newY);
	void create(double _positionX, double _positionY, Weapon weapon);
	void setAngleWatching(double angle);

	Enemy();
	~Enemy();
};

