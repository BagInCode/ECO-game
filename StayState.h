#pragma once
#include "State.h"

class StayState :
	public State
{
public:
	StayState();
	~StayState();

	void doAction(double _timer, Enemy& enemy, Player& player);
	int goNext(Enemy& enemy, Player& player);
	void findPath(Enemy& enemy, Player& player);
};

