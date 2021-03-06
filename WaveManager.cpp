#include "WaveManager.h"
#include "GameGraphicsManagerMinimap.h"
#include "GameGraphicsManagerInterface.h"
#include "safeManager.h"
#include "GlobalVariable.h"


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
	if (timer > TIME_BASE_BETWEEN_WAVE[GlobalVariable::gameLevel] + TIME_DIFF_BETWEEN_WAVE[GlobalVariable::gameLevel] * (numberOfWave - 1))
	{
		//if no enemy in game now
		if (int(game->Enemys.size()) == 0)
		{
			// autosafe
			game->Safe->safeGame(game);

			game->graphics->interface->addAction("AutoSafe", 5);
		}

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
		enemyWeapon.create(ENEMY_WEAPON_SHOOT_DELAY_TIME[GlobalVariable::gameLevel], ENEMY_WEAPON_SHOOT_DELAY_TIME[GlobalVariable::gameLevel],
						   ENEMY_WEAPON_BULLET_SPEED[GlobalVariable::gameLevel], ENEMY_WEAPON_ACCURACY[GlobalVariable::gameLevel],
						   ENEMY_WEAPON_BULLETS_PER_SHOOT[GlobalVariable::gameLevel], ENEMY_WEAPON_MAX_AMMO[GlobalVariable::gameLevel],
						   ENEMY_BULLET_DAMAGE[GlobalVariable::gameLevel], &(game->Bullets), &(game->rnd));
		enemyWeapon.addBullets(1000);

		// create enemy
		Enemy enemy;
		enemy.create(spawnPoint.first * SQUARE_SIZE_PIXIL + game->rnd() % SQUARE_SIZE_PIXIL, spawnPoint.second * SQUARE_SIZE_PIXIL + game->rnd() % SQUARE_SIZE_PIXIL, enemyWeapon);

		// add enemy to game
		game->Enemys.push_back(enemy);
		game->EnemysState.push_back(new OutOfVisibilityState());
	}

	game->playerObject.addEngramPoints(1);

	return;
}

pair < int, int > Game::WaveManager::randomSpawnPoint(Game* game)
{
	// get player cell position
	double playerX = game->playerObject.getPosition().first / FIELD_SIZE;
	double playerY = game->playerObject.getPosition().second / FIELD_SIZE;

	// while true
	for (;;)
	{
		// random position
		int x = game->rnd() % FIELD_SIZE;
		int y = game->rnd() % FIELD_SIZE;

		// if it is too close to borders
		if (x < 3 || x > FIELD_SIZE - 3 ||
			y < 3 || y > FIELD_SIZE - 3)
		{
			// continue
			continue;
		}

		// if this sqaure is visible for player
		if (game->graphics->minimap->isVisible(int(playerX), int(playerY), x, y))
		{
			// continue
			continue;
		}

		// return position
		return{ x, y };
	}
}

double Game::WaveManager::getTimeToWave()
{
	/*
	* function of getting time to next wave
	*
	* @return timer to next wave
	*/

	return TIME_BASE_BETWEEN_WAVE[GlobalVariable::gameLevel] + TIME_DIFF_BETWEEN_WAVE[GlobalVariable::gameLevel] * (numberOfWave - 1) - timer;
}

int Game::WaveManager::getNumberOfWave()
{
	/*
	* function of getting number of next wave
	*
	* @return number of next wave
	*/

	return numberOfWave;
}

void Game::WaveManager::load(int waveData)
{
	/*
	* function of loading
	*
	* @param waveData - data about waves
	*/

	// set number of wave, set timer to 10 sec before next wave
	numberOfWave = waveData;
	timer = TIME_BASE_BETWEEN_WAVE[GlobalVariable::gameLevel] + TIME_DIFF_BETWEEN_WAVE[GlobalVariable::gameLevel] * (numberOfWave - 1) - 10000;
}

void Game::WaveManager::safe(ofstream& out, int& safeOption, void(*updSafeOption)(int&, int))
{
	/*
	* function of saving
	*/

	updSafeOption(safeOption, 1);
	out << "1\n";

	updSafeOption(safeOption, numberOfWave);

	out << numberOfWave << "\n";

	return;
}