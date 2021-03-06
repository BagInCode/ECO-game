#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>

#include "Enemy.h"

#include "Constants.db"

using namespace std;
using namespace sf;

class State
{
protected:
	double timer = 0.000;
	double maxTimer = 0.000;

	int countShoots = 0;
	int maxCountShoots = 0;

	int stateType;

public:
	virtual void doAction(double _timer, Enemy& enemy, Player& player) = 0;
	virtual int goNext(Enemy& enemy, Player& player) = 0;
	virtual void randomizeState(mt19937* rnd) = 0;
	
	int getSateType() { return stateType; };
};

