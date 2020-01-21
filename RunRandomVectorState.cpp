#include "RunRandomVectorState.h"


RunRandomVectorState::RunRandomVectorState()
{
}


RunRandomVectorState::~RunRandomVectorState()
{
}


void RunRandomVectorState::doAction(double _timer, Enemy& enemy, Player& player)
{
	/*
	* functionf of doing actions of state
	*
	* @param timer - how much time has been passed
	*        enemy - enemy
	*        player - player
	*/

	// if timer is zero
	if (abs(timer) < 1e-3)
	{
		// generate random value 
		double randomValue = rand();
		randomValue /= rand();

		// make it in range [0..2]
		for (; randomValue > 2; randomValue -= 2){}

		// set angle
		enemy.setAngleMoving(randomValue * acos(-1));
	}

	// move enemy
	enemy.move(_timer, ENEMY_SPEED);

	// increase timer
	timer += _timer;

	return;
}

void RunRandomVectorState::findPath(Enemy& enemy, Player& player)
{

}

int RunRandomVectorState::goNext(Enemy& enemy, Player& player)
{
	/*
	* function of checking is next state needed
	*
	* @param enemy - enemy
	*        player - player
	*/

	// if run too long
	if (timer > TIME_ENEMY_RUN)
	{
		// return pointer to stay state
		return 1;
	}

	return -1;
}