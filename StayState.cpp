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
	
	// calculate position in window
	pair < double, double > enemyPositionInWindow = player.getPositionInWindow();

	enemyPositionInWindow.first += enemy.getPosition().first - player.getPosition().first;
	enemyPositionInWindow.second += enemy.getPosition().second - player.getPosition().second;

	// if enemy in window
	if (enemyPositionInWindow.first < enemy.getSize().first / 2 || enemyPositionInWindow.first > WINDOW_LENGTH - enemy.getSize().first / 2 ||
		enemyPositionInWindow.second < enemy.getSize().first / 2 || enemyPositionInWindow.second > WINDOW_HIGH - enemy.getSize().first / 2)
	{
		// return pointer to run state
		return 4;
	}

	// if enemy stay too long
	if (timer > TIME_ENEMY_STAY)
	{
		// return pointer to shoot state
		return 2;
	}

	return -1;
}