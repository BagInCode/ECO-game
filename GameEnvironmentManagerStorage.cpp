#include "GameEnvironmentManagerStorage.h"
#include "GameGraphicsManagerInterface.h"

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

string Game::EnvironmentManager::Storage::intToString(int val)
{
	if (val == 0)
	{
		return "0";
	}

	string res;

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

	int weaponAmmo = game->rnd() % 100, firstAidKit = game->rnd() % 3, grenades = min(int(game->rnd() % 2 + 1), 10 - game->countsGrenades), bullets;

	if (weaponAmmo < 5)
	{
		bullets = PISTOL_MAX_AMMO / 2 * (2 + game->allPlayerWeapon[0].gainingAmmoEngrams);
		game->allPlayerWeapon[0].addBullets(bullets);
		game->graphics->interface->addAction("find " + intToString(bullets) + " bullets for pistol", 5);
	}
	else if (weaponAmmo < 20)
	{
		bullets = SHOTGUN_MAX_AMMO / 2 * (6 + game->allPlayerWeapon[1].gainingAmmoEngrams);
		game->allPlayerWeapon[1].addBullets(bullets);
		game->graphics->interface->addAction("find " + intToString(bullets) + " bullets for shotgun", 5);
	}
	else if (weaponAmmo < 60)
	{
		bullets = AK_MAX_AMMO / 2 * (2 + game->allPlayerWeapon[2].gainingAmmoEngrams);
		game->allPlayerWeapon[2].addBullets(bullets);
		game->graphics->interface->addAction("find " + intToString(bullets) + " bullets for AK", 5);
	}
	else if (weaponAmmo < 80)
	{
		bullets = MINIGUN_MAX_AMMO / 2 * (1 + game->allPlayerWeapon[3].gainingAmmoEngrams);
		game->allPlayerWeapon[3].addBullets(bullets);
		game->graphics->interface->addAction("find " + intToString(bullets) + " bullets for minigun", 5);
	}
	else if (weaponAmmo < 100)
	{
		bullets = SNIPER_MAX_AMMO / 2 * (2 + game->allPlayerWeapon[4].gainingAmmoEngrams);
		game->allPlayerWeapon[4].addBullets(bullets);
		game->graphics->interface->addAction("find " + intToString(bullets) + " bullets for sniper rifle", 5);
	}

	if (firstAidKit == 0 || game->playerObject.getHealthPoints() == 100)
	{

	}
	else if (firstAidKit == 1)
	{
		game->playerObject.addHealthPoints(10);
		game->graphics->interface->addAction("find small first aid kit", 5);
	}
	else if (firstAidKit == 2)
	{
		game->playerObject.addHealthPoints(20);
		game->graphics->interface->addAction("find big first aid kit", 5);
	}

	if (grenades != 0)
	{
		game->countsGrenades += grenades;

		if (grenades == 1)
		{
			game->graphics->interface->addAction("find 1 grenade", 5);
		}
		else
		{
			game->graphics->interface->addAction("find " + intToString(grenades) + " grenades", 5);
		}
	}
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