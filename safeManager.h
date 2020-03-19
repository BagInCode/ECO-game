#pragma once
#include "Game.h"
#include "GameGraphicsManager.h"

class Game::SafeManager
{
	Game::GraphicsManager* graphics;
	Game::GraphicsManager::Minimap* minimap;

public:
	SafeManager();
	~SafeManager();

	void safeGame(Game* game);
	bool loadGame(RenderWindow& window, Game* game);

	int isCorrectSafeData(string safeData);
	bool isCorrectSafe(vector < int >& loadedData);

	void splitInput(vector < int >& loadedData, Game* game);
};

