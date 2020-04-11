#include "safeManager.h"
#include "GameEnvironmentManager.h"
#include "GameGraphicsManagerMinimap.h"
#include "WaveManager.h"
#include "GlobalVariable.h"
#include <fstream>

Game::SafeManager::SafeManager()
{
}


Game::SafeManager::~SafeManager()
{
}

void updSafeOption(int& safeOption, int newValue)
{
	/*
	* function of updating safeOption value
	*/

	safeOption ^= newValue;
}

void Game::SafeManager::safeGame(Game* game)
{
	/*
	* function of saving game
	*
	* @param game - main game class
	*/

	ofstream out;
	out.open("safeFile.sf");

	int safeOption = 0;

	game->graphics->safe(out, safeOption, updSafeOption);
	game->environment->safe(out, safeOption, updSafeOption);
	game->safe(out, safeOption, updSafeOption);
	game->waves->safe(out, safeOption, updSafeOption);

	updSafeOption(safeOption, GlobalVariable::gameLevel);

	out << GlobalVariable::gameLevel << "\n" << safeOption;
}

bool Game::SafeManager::loadGame(RenderWindow& window, Game* game)
{
	/*
	* function of loading safe
	*
	* @return true - if loading complited
	*/

	vector < int > loadedData;

	if (!isCorrectSafe(loadedData))
	{
		return 0;
	}

	game->initComponents(window);
	game->clearGame();
	
	splitInput(loadedData, game);

	game->graphics->loadStorageFonts(game);

	return 1;
}

int Game::SafeManager::isCorrectSafeData(string safeData)
{
	/*
	* function of checking is safeData positive number of int type and convert it
	*
	* @param safeData - chars from safe file
	*
	* @return value less than zero, if input data isn`t positive number of int type
	*         else return input value
	*/

	// if number begin from zero and it is not zero
	if (safeData[0] == '0' && int(safeData.size()) != 1)
	{
		return -1;
	}

	// if number is too long for int type
	if (int(safeData.size()) > 10)
	{
		return -1;
	}

	int result = 0;

	for (int i = 0; i < int(safeData.size()); i++)
	{	
		// if there is not digit
		if (safeData[i] < '0' && safeData[i] > '9')
		{
			return -1;
		}

		// add digit to result
		result = result * 10 + safeData[i] - '0';
	}

	return result;
}

bool Game::SafeManager::isCorrectSafe(vector < int >& loadedData)
{
	/*
	* function of checking is safe file correct
	*
	* @result loadedData - data in safe file
	*         true - if safe file if correct
	*/

	ifstream in;
	in.open("safeFile.sf");

	string safeData;

	if (!in.is_open())
	{
		return 0;
	}

	if (!(in >> safeData) || isCorrectSafeData(safeData) < 0)
	{
		return 0;
	}

	loadedData.push_back(isCorrectSafeData(safeData));

	for (int i = 0; i < FIELD_SIZE; i++)
	{
		if (!(in >> safeData) || int(safeData.size()) != FIELD_SIZE)
		{
			return 0;
		}

		for (int j = 0; j < FIELD_SIZE; j++)
		{
			if (safeData[j] != '0' && safeData[j] != '1')
			{
				return 0;
			}

			loadedData.push_back(int(safeData[j] - '0'));
		}
	}

	while (in >> safeData)
	{
		int value = isCorrectSafeData(safeData);

		if (value < 0)
		{
			return 0;
		}

		loadedData.push_back(value);
	}

	if (int(loadedData.size()) != 10297)
	{
		return 0;
	}

	int safeOption = 0;

	for (int i = 0; i+1 < int(loadedData.size()); i++)
	{
		updSafeOption(safeOption, loadedData[i]);
	}

	if (safeOption != loadedData.back())
	{
		return 0;
	}

	loadedData.pop_back();

	return 1;
}

void Game::SafeManager::splitInput(vector < int >& loadedData, Game* game)
{
	int position = 0;

	vector < int > minimapData;
	int countMinimapData = loadedData[position];

	for (int i = 1; i <= position + countMinimapData; i++)
	{
		minimapData.push_back(loadedData[i]);
	}

	position += countMinimapData + 1;

	int countStoragesData = loadedData[position];
	vector < pair < pair < int, int >, int > > storagesData;

	for (int i = position + 1; i <= position + countStoragesData * 3; i += 3)
	{
		storagesData.push_back({ { loadedData[i], loadedData[i + 1] }, loadedData[i + 2]});
	}

	position += countStoragesData * 3 + 1;

	int countCradtingTablesData = loadedData[position];
	vector < pair < int, int > > craftingTablesData;

	for (int i = position + 1; i <= position + countCradtingTablesData * 2; i += 2)
	{
		craftingTablesData.push_back({ loadedData[i], loadedData[i + 1] });
	}

	position += countCradtingTablesData * 2 + 1;

	int countTreeData = loadedData[position];
	vector < pair < int, int > > treeData;

	for (int i = position + 1; i <= position + countTreeData * 2; i += 2)
	{
		treeData.push_back({ loadedData[i], loadedData[i + 1] });
	}

	position += countTreeData * 2 + 1;

	int countWeaponData = loadedData[position];
	int pointer = 0;
	vector < vector < int > > weaponData;
	weaponData.resize(countWeaponData);

	for (int i = position + 1; i <= position + countWeaponData * 6; i += 6)
	{
		for (int j = i; j < i + 6; j++)
		{
			weaponData[pointer].push_back(loadedData[j]);
		}

		pointer++;
	}

	position += countWeaponData * 6 + 1;

	int countGrenadeData = loadedData[position];
	int grenadeData = loadedData[position + 1];

	position += countGrenadeData + 1;

	int countKillData = loadedData[position];
	vector < int > killData;

	for (int i = position + 1; i <= position + countKillData; i++)
	{
		killData.push_back(loadedData[i]);
	}

	position += countKillData + 1;

	int countPlayerData = loadedData[position];
	vector < int > playerData;

	for (int i = position + 1; i <= position + countPlayerData; i++)
	{
		playerData.push_back(loadedData[i]);
	}

	position += countPlayerData + 1;

	int countWaveData = loadedData[position];
	int waveData = loadedData[position + 1];

	position += countWaveData + 1;

	int gameLevel = loadedData[position];

	game->graphics->minimap->load(minimapData);
	game->environment->load(storagesData, craftingTablesData, treeData);
	game->load(weaponData, grenadeData, killData, playerData);
	game->waves->load(waveData);

	GlobalVariable::gameLevel = gameLevel;
}