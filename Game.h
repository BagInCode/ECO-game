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
	Weapon PlayerWeapon;
	vector < Bullet > Bullets;

	vector < pair < pair < double, double >, pair < double, double > > > positionOfObjects;

	bool pause;

	bool isMinimapDrawing;

	bool loadSprites();
	bool initComponents();
	void checkTime(RenderWindow & window);
	void moveObjects();
	void drawPicture(RenderWindow & window);
	void switchEvent(Event event, RenderWindow & window);
	void makePause(int value = -1);
	void doActions();
	void fieldGeneration();
	void prepareToDrawing(RenderWindow & window);
	void checkIntersection();
	bool orientedArea(double x1, double y1, double x2, double y2, double x3, double y3);
	void drawMinimap(RenderWindow & window);
	void updateVision();
	int getManhetenDist(int x1, int y1, int x2, int y2);
	bool isVisible(int playerX, int playerY, int x, int y);

public:
	void process(RenderWindow & window);
};

