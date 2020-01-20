#include "ShootState.h"


ShootState::ShootState()
{
}


ShootState::~ShootState()
{
}


void ShootState::doAction(double _timer, Enemy& enemy, Player& player)
{
	/*
	* functionf of doing actions of state
	*
	* @param timer - how much time has been passed
	*        enemy - enemy
	*        player - player
	*/

	// if shoot complited
	if (enemy.getWeaponPointer()->shoot(enemy.getPosition(), enemy.getAngleWatching(), 1))
	{
		// increase shoot timer
		countShoots++;
	}

	return;
}

void ShootState::findPath(Enemy& enemy, Player& player)
{

}

int ShootState::goNext(Enemy& enemy, Player& player)
{
	/*
	* function of checking is next state needed
	* 
	* @param enemy - enemy
	*        player - player
	*/

	//if count shoots enough
	if (countShoots == 3)
	{
		// return pointer to run state
		return 0;
	}

	return -1;
}