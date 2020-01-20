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

	// if run too long
	if (timer > TIME_ENEMY_RUN)
	{
		// return pointer to stay state
		return 1;
	}

	return -1;
}

void RunState::findPath(Enemy& enemy, Player& player)
{

}