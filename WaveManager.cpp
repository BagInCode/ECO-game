#include "WaveManager.h"


Game::WaveManager::WaveManager()
{
}


Game::WaveManager::~WaveManager()
{
}

void Game::WaveManager::checkTimer(double _timer, Game* game)
{
	/*
	* function of checking time between waves
	*
	* @param timer - how much time has been passed
	*        game - main game class
	*/

	// increase timer
	timer += _timer;

	// if there is time for new wave
	if (timer > TIME_BETWEN_WAVE)
	{
		// null timer
		timer = 0;

		// create wave
		createWave(numberOfWave, game);

		// increase number of wave
		numberOfWave++;
	}

	return;
}

void Game::WaveManager::createWave(int numberOfWave, Game* game)
{
	/*
	* function of creating waves
	*
	* @param numberOfWave - number of wave
	*        game - main game class
	*/

	// create 2 * number of wave bots
	for (int i = 0; i < 2 * numberOfWave; i++)
	{
		// choos spawn square
		pair < int, int > spawnPoint = randomSpawnPoint(game);

		// create enemy weapon
		Weapon enemyWeapon;
		enemyWeapon.create(1002, 1000, 1, 4 * acos(-1) / 180, 1, 30, 1, &(game->Bullets));

		// create enemy
		Enemy enemy;
		enemy.create(spawnPoint.first * SQUARE_SIZE_PIXIL + rand() % SQUARE_SIZE_PIXIL, spawnPoint.second * SQUARE_SIZE_PIXIL + rand() % SQUARE_SIZE_PIXIL, enemyWeapon);

		// add enemy to game
		game->Enemys.push_back(enemy);
		game->EnemysState.push_back(new OutOfVisibilityState());
	}

	return;
}

pair < int, int > Game::WaveManager::randomSpawnPoint(Game* game)
{
	// get player cell position
	int playerX = game->playerObject.getPosition().first / FIELD_SIZE;
	int playerY = game->playerObject.getPosition().second / FIELD_SIZE;

	// while true
	for (;;)
	{
		// random position
		int x = rand() % FIELD_SIZE;
		int y = rand() % FIELD_SIZE;

		// if it is too close to borders
		if (x < 3 || x > FIELD_SIZE - 3 ||
			y < 3 || y > FIELD_SIZE - 3)
		{
			// continue
			continue;
		}

		// if this sqaure is visible for player
		if (game->isVisible(playerX, playerY, x, y))
		{
			// continue
			continue;
		}

		// return position
		return{ x, y };
	}
}
