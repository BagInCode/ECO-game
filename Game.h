#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>

#include "Player.h"
#include "Bullet.h"
#include "Weapon.h"
#include "GamePausa.h"
#include "RunState.h"
#include "StayState.h"
#include "ShootState.h"
#include "RunRandomVectorState.h"
#include "OutOfVisibilityState.h"

#include "Constants.db"

class Game
{
	int gameOver;

	int Field[FIELD_SIZE][FIELD_SIZE];
	Player playerObject;

	bool visionMap[FIELD_SIZE][FIELD_SIZE];

	double timer;
	Clock myClock;

	Event event;

	Texture EnviromentTexture;
	vector < Sprite > EnviromentSprite;

	Texture MinimapTexture;
	vector < Sprite > MinimapSprite;

	bool playerShooting = 0;

	int currentWeaponPointer = 0;
	Weapon allPlayerWeapon[5];
	Sprite allPlayerSprite[5];

	Weapon currentPlayerWeapon;
	vector < Bullet > Bullets;

	vector < pair < pair < double, double >, pair < double, double > > > positionOfObjects;

	vector < Enemy > Enemys;
	vector < State* > EnemysState;
	
	bool isMinimapDrawing;

	bool loadSprites();
	bool initComponents();
	void checkTime(RenderWindow & window);
	void moveObjects();
	void drawPicture(RenderWindow & window);
	void switchEvent(Event event, RenderWindow & window);
	void doActions();
	void fieldGeneration();
	void checkIntersection();
	void checkIntersectionPlayer();
	void checkIntersectionEnemy(Enemy & enemy);
	bool checkIntersectionBullet(Bullet & bullet);
	bool orientedArea(double x1, double y1, double x2, double y2, double x3, double y3);
	void drawMinimap(RenderWindow & window);
	void updateVision();
	int getManhetenDist(int x1, int y1, int x2, int y2);
	bool isVisible(int playerX, int playerY, int x, int y);
	void checkGameOver();
	State* chooseNext(int next);
	void checkEnemyAlive();

public:
	void process(RenderWindow & window);
};

