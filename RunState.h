#pragma once
#include "State.h"

class RunState :
	public State
{
	int flag = -1;

public:
	RunState();
	~RunState();

	void doAction(double _timer, Enemy& enemy, Player& player);
	int goNext(Enemy& enemy, Player& player);
	void randomizeState(mt19937* rnd);
};

