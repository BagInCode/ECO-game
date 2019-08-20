/*
*
* created by @BagInCode
* for Eloped Crime Object Game
*
*/

#pragma once

#ifndef BULLET_CLASS
#define BULLET_CLASS

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
#include "Constants.db"

using namespace std;
using namespace sf;

class Bullet
{
	Texture bulletTexture;
	Sprite bulletSprite;

	double angle;

	double positionX;
	double positionY;

	double timeOfLife;

	bool isPlayerTarget;

	int damage;

public:
	Bullet();
	~Bullet();

	void setAngle(double newAngle);
	void setPosition(double newPositionX, double newPositionY);
	void setTerget(double newIsPlayerTarget);
	void setDamage(int newDamage);

	double getAngle();
	double getTimeOfLife();
	pair < double, double > getPosition();
	bool getTarget();
	int getDamage();

	bool loadSprite();
	bool create(double _angle, double _positionX, double _positionY, bool _isPlayerTarget, int _damage);
	void move(double timer);
	void draw(RenderWindow & window, double positionX, double positionY);
};

#endif
