#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <algorithm>

#include "Constants.db"

using namespace std;
using namespace sf;

class Player
{	
	int spriteHigh;
	int spriteLength;

	double angle = 0;

	int vectorX;
	int vectorY;

	double playerPositionX;
	double playerPositionY;

public:
	void create();
	void move(double timer);
	void setMoovingVector(int newVectorX, int newVectorY);
	pair < double, double > getPosition();
	pair < double, double > getPositionInWindow();
	pair < double, double > getSize();
	double rotate(RenderWindow & window);
	double getAngle();
	void setPosition(double newX, double newY);
};

