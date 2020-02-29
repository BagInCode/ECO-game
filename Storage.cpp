#include "Storage.h"

Storage::Storage(double x1, double x2, double y1, double y2, Font& font_) : x1(x1), x2(x2), y1(y1), y2(y2)
{
	lootable = 1;
	remainingTime = 0.0;

	font = &font_;

	textName.setFont(*font);
	textName.setString("storage");
	textName.setFillColor(Color::Green);
	textName.setCharacterSize(50);
	textName.setOutlineThickness(2);

	textInfo.setFont(*font);
	textInfo.setFillColor(Color::Green);
	textInfo.setCharacterSize(30);
	textInfo.setOutlineThickness(2);

	textPressKey.setFont(*font);
	textPressKey.setString("press E");
	textPressKey.setFillColor(Color::Green);
	textPressKey.setCharacterSize(30);
	textPressKey.setOutlineThickness(2);
}

Storage::~Storage()
{

}

string Storage::doubleToString(double a)
{
	string res;
	int val = a;

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

void Storage::update(double timer)
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

bool Storage::isLootable(double playerX, double playerY)
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

pair <int, int> Storage::tryToLoot(double playerX, double playerY)
{
	if (!isLootable(playerX, playerY))
	{
		return{ -1, 0 };
	}

	lootable = 0;
	remainingTime = 300.0;

	int a = rand() % 7;

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
}

void Storage::draw(RenderWindow* window, double baseX, double baseY, double playerX, double playerY, Sprite& storageSprite)
{
	double startPositionX = x1 - baseX, startPositionY = y1 - baseY;

	storageSprite.setPosition(startPositionX, startPositionY);
	window->draw(storageSprite);

	textName.setPosition(
		startPositionX + FIELD_SIZE - textName.getGlobalBounds().width / 2,
		startPositionY - textName.getGlobalBounds().height / 2 + 100
		);
	window->draw(textName);

	if (lootable)
	{
		textInfo.setString("lootable");
		textInfo.setPosition(
			startPositionX + FIELD_SIZE - textInfo.getGlobalBounds().width / 2,
			startPositionY - textInfo.getGlobalBounds().height / 2 + 150
			);
		window->draw(textInfo);

		if (isLootable(playerX, playerY))
		{
			textPressKey.setPosition(
				startPositionX + FIELD_SIZE - textPressKey.getGlobalBounds().width / 2,
				startPositionY - textPressKey.getGlobalBounds().height / 2 + 190
				);
			window->draw(textPressKey);
		}
	}
	else
	{
		textInfo.setString(doubleToString(remainingTime) + "s remains");
		textInfo.setPosition(
			startPositionX + FIELD_SIZE - textInfo.getGlobalBounds().width / 2,
			startPositionY - textInfo.getGlobalBounds().height / 2 + 150
			);
		window->draw(textInfo);
	}
}