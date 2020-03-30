#pragma once
#include "State.h"
class CloseObjectState :
	public State
{
public:
	void doAction(double _timer, Enemy& enemy, Player& player);
	int goNext(Enemy& enemy, Player& player);
	void randomizeState(mt19937* rnd);

	void chooseMovingVector(Enemy& enemy);

	CloseObjectState();
	~CloseObjectState();
};

