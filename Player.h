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
	Sprite PlayerSprite;
	Texture PlayerTexture;
	
	int spriteHigh;
	int spriteLength;

	double angle = 0;

	int vectorX;
	int vectorY;

	double playerPositionX;
	double playerPositionY;

public:
	bool create();
	void setSprite(int spritePositionX, int spritePositionY, int newSpriteLength, int newSpriteHigh);
	void draw(RenderWindow& window);
	void move(double timer);
	void setMoovingVector(int newVectorX, int newVectorY);
	pair < double, double > getPosition();
	pair < double, double > getPositionInWindow();
	void rotate(RenderWindow & window, double positionX, double poisitionY);
	double getAngle();
};

