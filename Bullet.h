#pragma once

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>

#include "Constants.db"

using namespace std;
using namespace sf;

class Bullet
{
	double angle;

	double positionX;
	double positionY;

	pair < double, double > previousPosition;

	double speed;

	int bulletId;

	int damage;

	bool isPlayerTarget;

	double timerOfLife = 0;
public:

	Bullet();
	~Bullet();

	void create(double _positionX, double _positionY, double _angle, double _speed, int _damage, bool _isPlayerTarget);
	void move(double timer);
	bool readyToDelete();

	pair < double, double > getPosition();
	pair < double, double > getPreviousPosition();

	bool getIsPlayerTarget();
	int getDamage();
};

