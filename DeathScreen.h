#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
#include <random>
#include <time.h>

#include "Constants.db"

using namespace std;
using namespace sf;

class DeathScreen
{
	Text DeathText;
	Font font;

	Color color;

	double timer = 0;

	Clock myClock;

	void initComponents();

	void firstScene(RenderWindow* window);
	void secondScene(RenderWindow* window);
	void showResult(vector < int > parametrs, RenderWindow* window);

	string toString(int x);

public:

	void process(vector < int > parametrs, RenderWindow* window);

	DeathScreen();
	~DeathScreen();
};

