/*
*
* created by @BagInCode
* for Eloped Crime Object Game
*
*/

#pragma once

#ifndef PLAYER_CLASS
#define PLAYER_CLASS

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

class Player
{
	Texture PlayerTexture;
	Sprite PlayerSpirite;

	double positionX = 0;
	double positionY = 0;

	double angle = 0;

	int healthPoints = 0;
	int armorPoints = 0;

	bool keyUpMovePressed = 0;
	bool keyDownMovePressed = 0;
	bool keyLeftMovePressed = 0;
	bool keyRightMovePressed = 0;

public:
	Player();
	~Player();

	pair < double, double > getPosition();
	pair < double, double > getPositionInWindow();
	double getAngle();
	int getHealthPoints();
	int getArmorPoints();

	void setPosition(double newPositionX, double newPositionY);
	void setArmorPoints(int newArmorPoints);
	void setHealthPoints(int newHealthPoints);
	void setKeyUpPressed(bool newValue);
	void setKeyDownPressed(bool newValue);
	void setKeyLeftPressed(bool newValue);
	void setKeyRightPressed(bool newValue);

	void move(double timer);
	void draw(RenderWindow & window);
	bool loadSprite();

	bool create(double newPositionX, double newPositionY, int healthPoints, int armorPoints);
};

#endif