#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.db"

#include <string>
#include <algorithm>

using namespace sf;
using namespace std;

class Storage
{
	int lootable;
	double remainingTime;

	Font* font;
	Text textName, textInfo, textPressKey;

	string doubleToString(double a);

public:

	double x1, x2, y1, y2;

	Storage(double x1, double x2, double y1, double y2, Font& textFont);
	~Storage();

	void update(double timer);
	bool isLootable(double playerX, double playerY);
	pair <int, int> tryToLoot(double playerX, double playerY); // return {gun type, ammo count}
	void draw(RenderWindow* window, double baseX, double baseY, double playerX, double playerY, Sprite& storageSprite);

};