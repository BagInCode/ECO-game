#include "OutOfVisibilityState.h"


OutOfVisibilityState::OutOfVisibilityState()
{
}


OutOfVisibilityState::~OutOfVisibilityState()
{
}

void OutOfVisibilityState::doAction(double _timer, Enemy& enemy, Player& player)
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
	enemy.move(_timer, 2*ENEMY_SPEED);

	// remember how much time has been passed
	timer = _timer;
	
	return;
}

int OutOfVisibilityState::goNext(Enemy& enemy, Player& player)
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
	if (enemyPositionInWindow.first > enemy.getSize().first / 2 && enemyPositionInWindow.first < WINDOW_LENGTH - enemy.getSize().first / 2 &&
		enemyPositionInWindow.second > enemy.getSize().first / 2 && enemyPositionInWindow.second < WINDOW_HIGH - enemy.getSize().first / 2)
	{
		// return pointer to run state
		return 0;
	}

	pair < double, double > currentPosition = enemy.getPosition();
	pair < double, double > previousPosition = enemy.getPreviousPosition();

	// calculate walked dist
	double dist = sqrt((currentPosition.first - previousPosition.first)*(currentPosition.first - previousPosition.first) +
					   (currentPosition.second - previousPosition.second)*(currentPosition.first - previousPosition.second));

	// if dist is too short
	if (dist < timer * ENEMY_SPEED)
	{
		// return pointer to run on random vector
		return 3;
	}

	return -1;
}


void OutOfVisibilityState::randomizeState()
{

}