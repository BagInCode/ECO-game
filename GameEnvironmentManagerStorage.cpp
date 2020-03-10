#include "GameEnvironmentManagerStorage.h"

Game::EnvironmentManager::Storage::Storage(double x1, double x2, double y1, double y2) : x1(x1), x2(x2), y1(y1), y2(y2)
{
	lootable = 1;
	remainingTime = 0.0;

	textName.setString("storage");
	textName.setFillColor(Color::Green);
	textName.setCharacterSize(50);
	textName.setOutlineThickness(2);

	textInfo.setFillColor(Color::Green);
	textInfo.setCharacterSize(30);
	textInfo.setOutlineThickness(2);

	textPressKey.setString("press E");
	textPressKey.setFillColor(Color::Green);
	textPressKey.setCharacterSize(30);
	textPressKey.setOutlineThickness(2);
}

Game::EnvironmentManager::Storage::~Storage()
{

}

void Game::EnvironmentManager::Storage::setFont(Font& newFont)
{
	font = &newFont;
	textName.setFont(*font);
	textInfo.setFont(*font);
	textPressKey.setFont(*font);
}

string Game::EnvironmentManager::Storage::doubleToString(double a)
{
	string res;
	int val = int(a);

	if (val == 0)
	{
		return "0";
	}

	while (val > 0)
	{
		res += char(val % 10 + '0');
		val /= 10;
	}

	reverse(res.begin(), res.end());

	return res;
}

void Game::EnvironmentManager::Storage::update(double timer)
{
	if (lootable == 1)
	{
		return;
	}

	remainingTime -= timer / 1000.0;

	if (remainingTime <= 0.0)
	{
		lootable = 1;
		remainingTime = 0.0;
	}
}

bool Game::EnvironmentManager::Storage::isLootable(double playerX, double playerY)
{
	if (lootable == 0)
	{
		return 0;
	}

	if (x1 <= playerX && playerX <= x2)
	{
		double dist = min(abs(playerY - y1), abs(playerY - y2));

		if (dist < PLAYER_SPRITE_AK_HIGH + 5.0)
		{
			return 1;
		}

		return 0;
	}

	if (y1 <= playerY && playerY <= y2)
	{
		double dist = min(abs(playerX - x1), abs(playerX - x2));

		if (dist < PLAYER_SPRITE_AK_LENGTH + 5.0)
		{
			return 1;
		}

		return 0;
	}

	return 0;
}

void Game::EnvironmentManager::Storage::tryToLoot(Game* game, double playerX, double playerY)
{
	if (!isLootable(playerX, playerY))
	{
		return;
	}

	lootable = 0;
	remainingTime = 300.0;

	// todo loting process
	int a = rand() % 7;
	
	/*
	if (a == 0)
	{
		return{ 0, 10 };
	}
	else if (a == 1)
	{
		return{ 1, 2 };
	}
	else if (a == 2)
	{
		return{ 2, 30 };
	}
	else if (a == 3)
	{
		return{ 3, 100 };
	}
	else if (a == 4)
	{
		return{ 4, 5 };
	}
	else
	{
		return{ -1, 0 };
	}
	*/
}

void Game::EnvironmentManager::Storage::draw(RenderWindow* window, double baseX, double baseY, double playerX, double playerY, Sprite& storageSprite)
{
	double startPositionX = x1 - baseX, startPositionY = y1 - baseY;

	storageSprite.setPosition(float(startPositionX), float(startPositionY));
	window->draw(storageSprite);

	textName.setPosition(
		float(startPositionX + FIELD_SIZE - textName.getGlobalBounds().width / 2.0),
		float(startPositionY - textName.getGlobalBounds().height / 2.0 + 100.0)
		);
	window->draw(textName);

	if (lootable)
	{
		textInfo.setString("lootable");
		textInfo.setPosition(
			float(startPositionX + FIELD_SIZE - textInfo.getGlobalBounds().width / 2.0),
			float(startPositionY - textInfo.getGlobalBounds().height / 2.0 + 150.0)
			);
		window->draw(textInfo);

		if (isLootable(playerX, playerY))
		{
			textPressKey.setPosition(
				float(startPositionX + FIELD_SIZE - textPressKey.getGlobalBounds().width / 2.0),
				float(startPositionY - textPressKey.getGlobalBounds().height / 2.0 + 190.0)
				);
			window->draw(textPressKey);
		}
	}
	else
	{
		textInfo.setString(doubleToString(remainingTime) + "s remains");
		textInfo.setPosition(
			float(startPositionX + FIELD_SIZE - textInfo.getGlobalBounds().width / 2.0),
			float(startPositionY - textInfo.getGlobalBounds().height / 2.0 + 150.0)
			);
		window->draw(textInfo);
	}
}