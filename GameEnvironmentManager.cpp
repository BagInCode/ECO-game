#include "GameEnvironmentManager.h"
#include "GameEnvironmentManagerStorage.h"
#include "GameGraphicsManagerInterface.h"

void Game::EnvironmentManager::initComponents()
{
	fieldGeneration();
}

void Game::EnvironmentManager::fieldGeneration()
{
	/*
	* function of generating field
	*/

	/// make random more randomly
	srand((unsigned int)time(NULL));

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
	for (int i = 0; i < FIELD_SIZE / 10; i++)
	{
		for (int j = 0; j < FIELD_SIZE / 10; j++)
		{
			// random position of house
			x = rand() % 7;
			y = rand() % 7;

			storageNumber[i * 10 + y][j * 10 + x] = storageIndex;
			storageIndex++;
			storages.push_back(new Game::EnvironmentManager::Storage((j * 10 + x) * SQUARE_SIZE_PIXIL, (j * 10 + x + 2) * SQUARE_SIZE_PIXIL,
				(i * 10 + y) * SQUARE_SIZE_PIXIL, (i * 10 + y + 3) * SQUARE_SIZE_PIXIL));

			// in other square of house set pointer, that they are not empty
			field[i * 10 + y][j * 10 + x] = -1;
			field[i * 10 + y + 1][j * 10 + x] = -1;
			field[i * 10 + y + 2][j * 10 + x] = -1;
			field[i * 10 + y][j * 10 + x + 1] = -1;
			field[i * 10 + y + 1][j * 10 + x + 1] = -1;
			field[i * 10 + y + 2][j * 10 + x + 1] = -1;


			// generate tree
			for (int k = 0; k < COUNT_TREES_IN_SQUARE; k++)
			{
				// generete while not get empty square
				while (1)
				{
					// random position
					x = rand() % 10;
					y = rand() % 10;

					// if square is empty
					if (field[i * 10 + x][j * 10 + y] == 0)
					{
						// set tree in this square
						field[i * 10 + x][j * 10 + y] = 5;

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
				x = rand() % 34;
				y = rand() % 34;

				if (field[i * 33 + x][j * 33 + y] == 0)
				{
					field[i * 33 + x][j * 33 + y] = 4;

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
	if (field[int(playerPositionY / SQUARE_SIZE_PIXIL)][int(playerPositionX / SQUARE_SIZE_PIXIL)] == 4)
	{
		return 1;
	}
	else
	{
		return 0;
	}
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