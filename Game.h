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
#include "Storage.h"

#include "Constants.db"

class Game
{
private:

	class GraphicsManager;

	RenderWindow* window;

	int gameOver;

	int Field[FIELD_SIZE][FIELD_SIZE];
	int storageNumber[FIELD_SIZE][FIELD_SIZE]; // hold index of storage in storages (for top left corner) or -1 otherwise
	Player playerObject;

	bool visionMap[FIELD_SIZE][FIELD_SIZE];

	double timer;
	Clock myClock;

	Event event;

	Font storageFont;
	vector<Storage> storages;

	bool playerShooting = 0;

	int currentWeaponPointer = 0;
	Weapon allPlayerWeapon[5];

	vector < Bullet > Bullets;

	vector < Enemy > Enemys;
	vector < State* > EnemysState;

	GraphicsManager* graphics;

	bool initComponents();
	void checkTime();
	void moveObjects();
	void switchEvent(Event event);
	void doActions();
	void fieldGeneration();
	void checkIntersection();
	void checkIntersectionPlayer();
	void checkIntersectionEnemy(Enemy & enemy);
	bool checkIntersectionBullet(Bullet & bullet);
	bool orientedArea(double x1, double y1, double x2, double y2, double x3, double y3);
	void updateVision();
	int getManhetenDist(int x1, int y1, int x2, int y2);
	bool isVisible(int playerX, int playerY, int x, int y);
	void checkGameOver();
	State* chooseNext(int next);
	void checkEnemyAlive();

public:

	Game();
	~Game();

	void process(RenderWindow & window);
};