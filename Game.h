/*
*
* created by @BagInCode
* for Eloped Crime Object Game
*
*/

#pragma once


#ifndef GAME_CLASS
#define GAME_CLASS

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
#include <queue>

#include "Player.h";
#include "Bullet.h";
#include "Constants.db";
#include "Weapon.h"
#include "Enemy.h"

using namespace std;
using namespace sf;

class Game
{
	int Field[FIELD_HIGH][FIELD_LENGTH];
	int PlayerWeaponNumber = 0;

	Player PlayerObject;

	Texture EnviromentTexture;
	vector < Sprite > enviroment;
	vector < Sprite > road;
	vector < Bullet > bullets;
	vector < Enemy > enemies;
	Weapon PlayerWeapons[10];
	

	Clock myClock;

	Event MoveUp;
	Event MoveDown;
	Event MoveLeft;
	Event MoveRight;
	Event Shoot;

	bool pause = 0;
	bool shooting = 0;

public:
	Game();
	~Game();

	bool equal(Event a, Event b);

	bool loadSprites();
	bool createPlayer(double newPositionX, double newPositionY, int healthPoints, int armorPoints);
	bool loadSave(double & newPositionX, double & newPositionY, int & healthPoints, int & armorPoints);
	void loadDefault(double & newPositionX, double & newPositionY, int & healthPoints, int & armorPoints);
	bool loadGame();
	bool createEnemies();

	void generateField();

	int getRoadNumber(int positionX, int positionY);
	void checkIntersections();
	void checkTime(RenderWindow & window);
	void drawObjects(RenderWindow & window);
	void moveObjects(double timer);
	bool switchEvent(Event & event);
	void makePause(bool isPause);
	void saveGame();
	void initBullet(Enemy & enemy);
	bool initBullet();
	void checkPlayerGun(double timer);
	void checkBullets();

	void game(RenderWindow & window);
};

#endif
