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
#include "Grenade.h"

#include "Constants.db"

class Game
{
private:

	class GraphicsManager;
	class EnvironmentManager;
	class WaveManager;

	RenderWindow* window;

	int gameOver;

	Player playerObject;

	double timer;
	Clock myClock;

	Event event;

	bool playerShooting = 0;

	int currentWeaponPointer = 0;
	Weapon allPlayerWeapon[5];

	vector < Bullet > Bullets;

	vector < Enemy > Enemys;
	vector < State* > EnemysState;

	int countsGrenades = 10;
	vector < Grenade > grenades;

	GraphicsManager* graphics;
	EnvironmentManager* environment;
	WaveManager* waves;

	bool isKeyAPressed = 0;
	bool isKeySPressed = 0;
	bool isKeyWPressed = 0;
	bool isKeyDPressed = 0;

	bool initComponents();
	void checkTime();
	void moveObjects();
	void switchEvent(Event event);
	void doActions();
	void checkIntersection();
	void checkIntersectionPlayer();
	void checkIntersectionEnemy(Enemy & enemy);
	bool checkIntersectionBullet(Bullet & bullet);
	bool orientedArea(double x1, double y1, double x2, double y2, double x3, double y3);
	void checkGameOver();
	State* chooseNext(int next);
	void checkEnemyAlive();
	void checkGranades();

public:

	Game();
	~Game();

	void process(RenderWindow & window);
};