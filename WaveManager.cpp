#include "WaveManager.h"


Game::WaveManager::WaveManager()
{
}


Game::WaveManager::~WaveManager()
{
}

void Game::WaveManager::checkTimer(double _timer, Game* game)
{
	timer += _timer;

	if (timer > TIME_BETWEN_WAVE)
	{
		timer = 0;

		createWave(numberOfWave, game);

		numberOfWave++;
	}
}

void Game::WaveManager::createWave(int numberOfWave, Game* game)
{
	for (int i = 0; i < 3 * numberOfWave; i++)
	{
		pair < int, int > spawnPoint = randomSpawnPoint(game);

		Weapon enemyWeapon;
		enemyWeapon.create(330, 330, 1, 3 * acos(-1) / 180, 1, 30, 0, &(game->Bullets));

		Enemy enemy;
		enemy.create(spawnPoint.first * SQUARE_SIZE_PIXIL, spawnPoint.second * SQUARE_SIZE_PIXIL, enemyWeapon);

		game->Enemys.push_back(enemy);
		game->EnemysState.push_back(new OutOfVisibilityState());
	}

	return;
}

pair < int, int > Game::WaveManager::randomSpawnPoint(Game* game)
{
	int playerX = game->playerObject.getPosition().first / FIELD_SIZE;
	int playerY = game->playerObject.getPosition().second / FIELD_SIZE;

	for (;;)
	{
		int x = rand() % FIELD_SIZE;
		int y = rand() % FIELD_SIZE;

		if (x < 3 || x > FIELD_SIZE - 3 ||
			y < 3 || y > FIELD_SIZE - 3)
		{
			continue;
		}

		if (game->isVisible(playerX, playerY, x, y))
		{
			continue;
		}

		return { x, y };
	}
}
