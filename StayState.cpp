#include "StayState.h"


StayState::StayState()
{
}


StayState::~StayState()
{
}


void StayState::doAction(double _timer, Enemy& enemy, Player& player)
{
	/*
	* functionf of doing actions of state
	*
	* @param timer - how much time has been passed
	*        enemy - enemy
	*        player - player
	*/

	// increase timer
	timer += _timer;

	return;
}

int StayState::goNext(Enemy& enemy, Player& player)
{
	/*
	* function of checking is next state needed
	*
	* @param enemy - enemy
	*        player - player
	*/

	// if enemy stay too long
	if (timer > TIME_ENEMY_STAY)
	{
		// return pointer to shoot state
		return 2;
	}

	return -1;
}

void StayState::findPath(Enemy& enemy, Player& player)
{

}