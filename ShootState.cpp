#include "ShootState.h"


ShootState::ShootState()
{
	stateType = 2;
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

int ShootState::goNext(Enemy& enemy, Player& player)
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

	// if enemy out of window
	if (enemyPositionInWindow.first < enemy.getSize().first / 2 || enemyPositionInWindow.first > WINDOW_LENGTH - enemy.getSize().first / 2 ||
		enemyPositionInWindow.second < enemy.getSize().first / 2 || enemyPositionInWindow.second > WINDOW_HIGH - enemy.getSize().first / 2)
	{
		// return pointer to run state
		return 4;
	}

	//if count shoots enough
	if (countShoots == maxCountShoots)
	{
		// with probability near 25% 
		if (enemy.getWeaponPointer()->rnd->operator()() % 4 == 0)
		{
			// next state is run on random vector
			return 3;
		}

		// return pointer to run state
		return 0;
	}

	return -1;
}

void ShootState::randomizeState(mt19937* rnd)
{
	/*
	* function of randomizing state
	*/

	// randomize max time of stay
	maxCountShoots = COUNT_ENEMY_SHOOT + (int(rnd->operator()() % 5) - 2);
}