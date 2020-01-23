#pragma once
#include "State.h"

class ShootState :
	public State
{
public:
	ShootState();
	~ShootState();

	void doAction(double _timer, Enemy& enemy, Player& player);
	int goNext(Enemy& enemy, Player& player);
};

