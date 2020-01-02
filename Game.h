#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>

#include "Player.h"
#include "Bullet.h"
#include "Weapon.h"

#include "Constants.db"

class Game
{
	int Field[FIELD_SIZE][FIELD_SIZE];
	Player playerObject;

	double timer;
	Clock myClock;

	Event event;

	Texture EnviromentTexture;
	vector < Sprite > EnviromentSprite;

	CircleShape bulletSprite;

	bool playerShooting = 0;
	Weapon PlayerWeapon;
	vector < Bullet > Bullets;

	bool pause;

	bool initComponents();
	void checkTime(RenderWindow & window);
	void moveObjects();
	void drawPicture(RenderWindow & window);
	void switchEvent(Event event, RenderWindow & window);
	void makePause();
	void doActions();

public:
	void process(RenderWindow & window);
};

