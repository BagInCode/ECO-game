#pragma once
#include "State.h"

class RunState :
	public State
{
public:
	RunState();
	~RunState();

	void doAction(double _timer, Enemy& enemy, Player& player);
	int goNext(Enemy& enemy, Player& player);
	void findPath(Enemy& enemy, Player& player);
};

