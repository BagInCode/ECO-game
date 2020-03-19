#pragma once

#include "Game.h"

class Game::WaveManager
{
	double timer = 0;
	int numberOfWave = 1;

public:
	void checkTimer(double _timer, Game* game);
	void createWave(int numberOfWave, Game* game);
	pair < int, int > randomSpawnPoint(Game* game);

	double getTimeToWave();
	int getNumberOfWave();

	void load(int waveData);

	void safe(ofstream& out, int& safeOption, void(*updSafeOption)(int&, int));

	WaveManager();
	~WaveManager();
};

