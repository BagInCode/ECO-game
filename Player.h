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

	int healthPoints;

	int engramPoints;

public:
	int isDamaged;
	int armor;

	void create();
	void move(double timer);
	void setMovingVector(int newVectorX, int newVectorY);
	void updateMovingVector(int deltX, int deltY);
	pair < double, double > getPosition();
	pair < double, double > getPositionInWindow();
	pair < double, double > getSize();
	double rotate(RenderWindow* window);
	double getAngle();
	void setPosition(double newX, double newY);
	int getHealthPoints();
	int getEngramPoints();
	void addEngramPoints(int value);
	void decrEngramPoints(int value);
	void getDamage(int damage);
	void setSize(double length, double high);
};

