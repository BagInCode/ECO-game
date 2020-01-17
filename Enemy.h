#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <algorithm>

#include "BasicState.h"
#include "Weapon.h"

#include "Constants.db"

using namespace std;
using namespace sf;

class Enemy
{
	double positionX;
	double poditionY;

	double angleMoving;
	double angleWathcing;

	BasicState* myState;

	Weapon myWeapon;

	int healthPoints;

	double spriteLength;
	double spriteHigh;
public:

	void move(double timer);


	Enemy();
	~Enemy();
};

