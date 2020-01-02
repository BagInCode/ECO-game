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
public:
	double angle;

	double positionX;
	double positionY;

	double speed;

	int bulletId;

	int damage;

	bool isPlayerTarget;

	double timerOfLife = 0;

	Bullet();
	~Bullet();

	void create(double _positionX, double _positionY, double _angle, double _speed, int _damage, bool _isPlayerTarget);
	void move(double timer);
	bool readyToDelete();

	pair < double, double > getPosition();
};

