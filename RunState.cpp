#include "RunState.h"
#include "GlobalVariable.h"

RunState::RunState()
{
	stateType = 0;
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

	if (flag > -1)
	{
		enemy.setAngleMoving(flag*acos(-1) / 2);
	}

	// move enemy
	enemy.move(_timer, ENEMY_SPEED[GlobalVariable::gameLevel]);

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

	// get enemy current position and enemy previous position
	pair < double, double > enemyPreviousPosition = enemy.getPreviousPosition();
	pair < double, double > enemyPosition = enemy.getPosition();

	// calc dist of moving
	double deltX = enemyPosition.first - enemyPreviousPosition.first;
	double deltY = enemyPosition.second - enemyPreviousPosition.second;

	double dist = sqrt(deltX * deltX + deltY * deltY);

	// if enemy run to small dist
	if (dist * 2 < TIME_FOR_ACTION * ENEMY_SPEED[GlobalVariable::gameLevel])
	{
		timer = 0;
		maxTimer = 2000;

		double angle = enemy.getAngleMoving();

		if (abs(sin(angle)) > abs(cos(angle)))
		{
			if (rand() % 2)
			{
				flag = 0;
			}else
			{
				flag = 2;
			}
		}else
		{
			if (rand() % 2)
			{
				flag = 1;
			}else
			{
				flag = 3;
			}
		}
	}

	// if run too long
	if (timer > maxTimer)
	{
		// return pointer to stay state
		return 1;
	}

	return -1;
}

void RunState::randomizeState(mt19937* rnd)
{
	/*
	* function of randomizing state
	*/

	// randomize max time of stay
	maxTimer = TIME_ENEMY_STAY[GlobalVariable::gameLevel] + (int(rnd->operator()() % 401) - 200);
}