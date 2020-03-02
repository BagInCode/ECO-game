#pragma once

#include "State.h"

class OutOfVisibilityState :
	public State
{
public:
	OutOfVisibilityState();
	~OutOfVisibilityState();
	
	void doAction(double _timer, Enemy& enemy, Player& player);
	int goNext(Enemy& enemy, Player& player);
	void randomizeState();
};

