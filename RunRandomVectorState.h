#pragma once
#include "State.h"
class RunRandomVectorState :
	public State
{
public:
	RunRandomVectorState();
	~RunRandomVectorState();

	void doAction(double _timer, Enemy& enemy, Player& player);
	void findPath(Enemy& enemy, Player& player);
	int goNext(Enemy& enemy, Player& player);
};
