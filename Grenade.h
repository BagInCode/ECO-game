#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>

#include "Player.h"

#include "Constants.db"

class Grenade
{
	double speed;
	double angle;

	double timer;

	double positionX;
	double positionY;

	int numberPictureToDraw;

	bool detonate;

public:
	Grenade();
	~Grenade();

	void create(Player& player, RenderWindow* window);
	void move(double _timer);
	double calculteSpeed(Player& player, RenderWindow* window);

	pair < double, double > getPosition();

	int getNumberOfPicture();
	
	bool timeToDelete();
	bool isDetonate();
};

