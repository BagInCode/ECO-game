#include "RunState.h"


RunState::RunState()
{
}


RunState::~RunState()
{
}

void RunState::doAction(double _timer, Enemy& enemy, Player& player)
{
	/*
	* functionf of doing actions of state
	*
	* @param timer - how much time has been passed
	*        enemy - enemy
	*        player - player
	*/

	// get coordinates vector (enemy -> player)
	double deltX = player.getPosition().first - enemy.getPosition().first;
	double deltY = player.getPosition().second - enemy.getPosition().second;

	// get angle from enemy to player
	double angle = atan2(deltY, deltX);

	// set angle oving to player
	enemy.setAngleMoving(angle);

	// move enemy
	enemy.move(_timer, ENEMY_SPEED);

	// increase timer
	timer += _timer;

	return;
}

int RunState::goNext(Enemy& enemy, Player& player)
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

void RunState::randomizeState()
{
	/*
	* function of randomizing state
	*/

	// randomize max time of stay
	maxTimer = TIME_ENEMY_STAY + ((rand() % 501) - 250);
}