#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <algorithm>
#include <random>

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
	int armor;

public:
	int isDamaged;

	Player();
	~Player();

	void setMovingVector(int newVectorX, int newVectorY);
	void updateMovingVector(int deltX, int deltY);

	pair < double, double > getPosition();
	void setPosition(double newX, double newY);

	pair < double, double > getSize();
	void setSize(double length, double high);

	pair < double, double > getPositionInWindow();
	double getAngle();

	int getHealthPoints();
	void addHealthPoints(int value);
	void setHP(int newHP);

	int getEngramPoints();
	void addEngramPoints(int value);
	void decrEngramPoints(int value);
	void setEngramPoints(int newEngramPoints);
	
	void getDamage(int damage, mt19937* rnd);

	void setArmor(int newArmor);
	int getArmor();

	void create();
	void move(double timer);
	double rotate(RenderWindow* window);
};

