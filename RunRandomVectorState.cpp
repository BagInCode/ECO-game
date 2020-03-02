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
		// generate random value in range [-1, 1] 
		double randomValue1 = (rand()%3) - 1;
		double randomValue2 = (rand()%10) + 1;

		double randomValue = randomValue1 / randomValue2;
		
		// set angle
		enemy.setAngleMoving(randomValue * acos(-1) / 2 + enemy.getAngleWatching());
	}

	// move enemy
	enemy.move(_timer, ENEMY_SPEED);

	// increase timer
	timer += _timer;

	return;
}

int RunRandomVectorState::goNext(Enemy& enemy, Player& player)
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

	// if run too long
	if (timer > maxTimer)
	{
		// return pointer to stay state
		return 1;
	}

	return -1;
}

void RunRandomVectorState::randomizeState()
{
	/*
	* function of randomizing state
	*/

	// randomize max time of stay
	maxTimer = TIME_ENEMY_STAY + ((rand() % 501) - 250);
}