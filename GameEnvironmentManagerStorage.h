#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.db"

#include "GameEnvironmentManager.h"

#include <string>
#include <algorithm>

using namespace sf;
using namespace std;

class Game::EnvironmentManager::Storage 
{
	int lootable;
	double remainingTime;

	Font* font;
	Text textName, textInfo, textPressKey;

	string doubleToString(double a);
	string intToString(int val);

public:

	double x1, x2, y1, y2;

	Storage(double x1, double x2, double y1, double y2);
	~Storage();

	void setFont(Font& newFont);

	double getRemainingTime();
	void setRemainingTime(int timer);

	bool isLootable(double playerX, double playerY);
	bool isLootable();
	void tryToLoot(Game* game, double playerX, double playerY);

	void update(double timer);
	void draw(RenderWindow* window, double baseX, double baseY, double playerX, double playerY, Sprite& storageSprite);
};