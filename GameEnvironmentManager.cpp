#include "GameEnvironmentManager.h"
#include "GameEnvironmentManagerStorage.h"
#include "GameGraphicsManagerInterface.h"

void Game::EnvironmentManager::initComponents(Game* game)
{
	fieldGeneration(game);
}

void Game::EnvironmentManager::fieldGeneration(Game* game)
{
	/*
	* function of generating field
	*/

	for (auto& row : field)
	{
		for (auto& cell : row)
		{
			cell = 0;
		}
	}

	for (auto& row : storageNumber)
	{
		for (auto& cell : row)
		{
			cell = -1;
		}
	}

	int x, y;

	int storageIndex = 0;
	// divide all fieald on squares 10x10 and random in each square independly
	for (int i = 0; i < FIELD_SIZE / BLOCK_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE / BLOCK_SIZE; j++)
		{
			// random position of house
			x = game->rnd() % (BLOCK_SIZE-3);
			y = game->rnd() % (BLOCK_SIZE - 3);

			storageNumber[i * BLOCK_SIZE + y][j * BLOCK_SIZE + x] = storageIndex;
			storageIndex++;
			storages.push_back(new Game::EnvironmentManager::Storage((j * BLOCK_SIZE + x) * SQUARE_SIZE_PIXIL, (j * BLOCK_SIZE + x + 2) * SQUARE_SIZE_PIXIL,
				(i * BLOCK_SIZE + y) * SQUARE_SIZE_PIXIL, (i * BLOCK_SIZE + y + 3) * SQUARE_SIZE_PIXIL));

			// in other square of house set pointer, that they are not empty
			field[i * BLOCK_SIZE + y][j * BLOCK_SIZE + x] = -1;
			field[i * BLOCK_SIZE + y + 1][j * BLOCK_SIZE + x] = -1;
			field[i * BLOCK_SIZE + y + 2][j * BLOCK_SIZE + x] = -1;
			field[i * BLOCK_SIZE + y][j * BLOCK_SIZE + x + 1] = -1;
			field[i * BLOCK_SIZE + y + 1][j * BLOCK_SIZE + x + 1] = -1;
			field[i * BLOCK_SIZE + y + 2][j * BLOCK_SIZE + x + 1] = -1;


			// generate tree
			for (int k = 0; k < COUNT_TREES_IN_BLOCK; k++)
			{
				// generete while not get empty square
				while (1)
				{
					// random position
					x = game->rnd() % BLOCK_SIZE;
					y = game->rnd() % BLOCK_SIZE;

					// if square is empty
					if (field[i * BLOCK_SIZE + x][j * BLOCK_SIZE + y] == 0)
					{
						// set tree in this square
						field[i * BLOCK_SIZE + x][j * BLOCK_SIZE + y] = 5;

						trees.push_back({ (j*BLOCK_SIZE + y + 0.5)*SQUARE_SIZE_PIXIL, (i*BLOCK_SIZE + x + 0.5)*SQUARE_SIZE_PIXIL });

						//stop generating
						break;
					}
				}
			}
		}
	}

	for (int i = 0; i < FIELD_SIZE / 33; i++)
	{
		for (int j = 0; j < FIELD_SIZE / 33; j++)
		{
			while (1)
			{
				x = game->rnd() % 34;
				y = game->rnd() % 34;

				if (field[i * 33 + x][j * 33 + y] == 0)
				{
					field[i * 33 + x][j * 33 + y] = 4;

					craftingTables.push_back({ { (j * 33 + y)*1.*SQUARE_SIZE_PIXIL, (j * 33 + y + 1)*1.*SQUARE_SIZE_PIXIL },
											   { (i * 33 + x)*1.*SQUARE_SIZE_PIXIL, (i * 33 + x + 1)*1.*SQUARE_SIZE_PIXIL } });

					break;
				}
			}
		}
	}
}

void Game::EnvironmentManager::update(double timer)
{
	for (auto& storage : storages)
	{
		storage->update(timer);
	}
}

int Game::EnvironmentManager::isNearCraftingTable(double playerPositionX, double playerPositionY)
{
	double playerSize = PLAYER_SNIPER_LENGTH;

	for (int i = 0; i < int(craftingTables.size()); i++)
	{
		if (playerPositionX > craftingTables[i].first.first - playerSize - 1 && playerPositionX < craftingTables[i].first.second + playerSize + 1 &&
			playerPositionY > craftingTables[i].second.first - playerSize - 1 && playerPositionY < craftingTables[i].second.second + playerSize + 1)
		{
			return 1;
		}
	}

	return 0;
}

void Game::EnvironmentManager::checkStoragesAction(Game* game, double playerPositionX, double playerPositionY)
{
	for (int i = max(0, int(playerPositionY / SQUARE_SIZE_PIXIL - 5)); i <= min(99, int(playerPositionY / SQUARE_SIZE_PIXIL + 5)); i++)
	{
		for (int j = max(0, int(playerPositionX / SQUARE_SIZE_PIXIL - 5)); j <= min(99, int(playerPositionX / SQUARE_SIZE_PIXIL + 5)); j++)
		{
			if (storageNumber[i][j] != -1)
			{
				if (storages[storageNumber[i][j]]->isLootable(playerPositionX, playerPositionY))
				{
					game->graphics->interface->addAction("Loot storage", 5.0);

					storages[storageNumber[i][j]]->tryToLoot(game, playerPositionX, playerPositionY);
				}
			}
		}
	}
}