#pragma once

#include "Game.h"

class Game::EnvironmentManager
{
public:

	class Storage;

	int field[FIELD_SIZE][FIELD_SIZE];
	int storageNumber[FIELD_SIZE][FIELD_SIZE]; // hold index of storage in storages (for top left corner) or -1 otherwise

	vector<Storage*> storages;

	void initComponents(Game* game);
	void fieldGeneration(Game* game);
	void update(double timer);

	int isNearCraftingTable(double playerPositionX, double playerPositionY);
	void checkStoragesAction(Game* game, double playerPositionX, double playerPositionY);

};