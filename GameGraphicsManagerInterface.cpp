#include "GameGraphicsManagerInterface.h"

Game::GraphicsManager::Interface::Interface()
{
	reloadingProgressBar = new ProgressBar(1150, 588, 140, 5, 2, 0);
}

Game::GraphicsManager::Interface::~Interface()
{
	delete reloadingProgressBar;
}

string Game::GraphicsManager::Interface::toString(int val)
{
	if (val == 0)
	{
		return "0";
	}

	string res;
	while (val > 0)
	{
		res += char('0' + val % 10);
		val /= 10;
	}

	reverse(res.begin(), res.end());

	return res;
}

void Game::GraphicsManager::Interface::initComponents()
{
	font.loadFromFile(GAME_GRAPHICS_MANAGER_INTERFACE_FONT_PATH);

	actionText.setFont(font);
	actionText.setCharacterSize(30);
	actionText.setFillColor(Color::Black);
	actionText.setOutlineThickness(2);
	actionText.setOutlineColor(Color::White);

	bulletCount.setFont(font);
	bulletCount.setCharacterSize(60);
	bulletCount.setFillColor(Color::Black);
	bulletCount.setOutlineThickness(1);
	bulletCount.setOutlineColor(Color::White);

	InterfaceTexture.loadFromFile(INTERFACE_TEXTURE);

	HPSprite.setTexture(InterfaceTexture);
	HPSprite.setTextureRect(IntRect(HP_INTERFACE_LEFT, HP_INTERFACE_TOP, INTERFACE_SPRITE_LENGTH, INTERFACE_SPRITE_HIGH));

	HPText.setFont(font);
	HPText.setCharacterSize(60);
	HPText.setFillColor(Color::Black);
	HPText.setOutlineThickness(1);
	HPText.setOutlineColor(Color::White);

	armorSprite.setTexture(InterfaceTexture);
	armorSprite.setTextureRect(IntRect(ARMOR_INTERFACE_LEFT, ARMOR_INTERFACE_TOP, INTERFACE_SPRITE_LENGTH, INTERFACE_SPRITE_HIGH));

	armorText.setFont(font);
	armorText.setCharacterSize(60);
	armorText.setFillColor(Color::Black);
	armorText.setOutlineThickness(1);
	armorText.setOutlineColor(Color::White);

	grenadeSprite.setTexture(InterfaceTexture);
	grenadeSprite.setTextureRect(IntRect(GRENADE_INTERFACE_LEFT, GRENADE_INTERFACE_TOP, INTERFACE_SPRITE_LENGTH, INTERFACE_SPRITE_HIGH));

	grenadeText.setFont(font);
	grenadeText.setCharacterSize(60);
	grenadeText.setFillColor(Color::Black);
	grenadeText.setOutlineThickness(1);
	grenadeText.setOutlineColor(Color::White);

	pistolSprite.setTexture(InterfaceTexture);
	pistolSprite.setTextureRect(IntRect(PISTOL_INTERFACE_POSITION_LEFT, PISTOL_INTERFACE_POSITION_TOP, INTERFACE_WEAPON_LENGTH, INTERFACE_WEAPON_HIGH));

	shotgunSprite.setTexture(InterfaceTexture);
	shotgunSprite.setTextureRect(IntRect(DOUBLE_INTERFACE_POSITION_LEFT, DOUBLE_INTERFACE_POSITION_TOP, INTERFACE_WEAPON_LENGTH, INTERFACE_WEAPON_HIGH));

	AKSprite.setTexture(InterfaceTexture);
	AKSprite.setTextureRect(IntRect(AK_INTERFACE_POSITION_LEFT, AK_INTERFACE_POSITION_TOP, INTERFACE_WEAPON_LENGTH, INTERFACE_WEAPON_HIGH));

	minigunSprite.setTexture(InterfaceTexture);
	minigunSprite.setTextureRect(IntRect(MINIGUN_INTERFACE_POSITION_LEFT, MINIGUN_INTERFACE_POSITION_TOP, INTERFACE_WEAPON_LENGTH, INTERFACE_WEAPON_HIGH));

	sniperSprite.setTexture(InterfaceTexture);
	sniperSprite.setTextureRect(IntRect(SNIPER_INTERFACE_POSITION_LEFT, SNIPER_INTERFACE_POSITION_TOP, INTERFACE_WEAPON_LENGTH, INTERFACE_WEAPON_HIGH));

	weaponInconPointer = &pistolSprite;
}

void Game::GraphicsManager::Interface::addAction(string text, double duration)
{
	for (auto& action : actions)
	{
		if (action.first.first == text)
		{
			action.second++;
			action.first.second = duration;

			return;
		}
	}

	actions.push_back({ { text, duration }, 1 });
}

void Game::GraphicsManager::Interface::update(Game* game, double timer)
{
	for (int i = int(actions.size()) - 1; i >= 0; i--)
	{
		actions[i].first.second -= timer / 1000.0;
		if (actions[i].first.second < 0)
		{
			actions.erase(actions.begin() + i);
		}
	}

	if (game->currentWeaponPointer == 0)
	{
		weaponInconPointer = &pistolSprite;
	}
	else if (game->currentWeaponPointer == 1)
	{
		weaponInconPointer = &shotgunSprite;
	}
	else if (game->currentWeaponPointer == 2)
	{
		weaponInconPointer = &AKSprite;
	}
	else if (game->currentWeaponPointer == 3)
	{
		weaponInconPointer = &minigunSprite;
	}
	else if (game->currentWeaponPointer == 4)
	{
		weaponInconPointer = &sniperSprite;
	}

	double reloadingPercentage = game->allPlayerWeapon[game->currentWeaponPointer].getTimer() /
		game->allPlayerWeapon[game->currentWeaponPointer].getReloadingTime();

	if (game->allPlayerWeapon[game->currentWeaponPointer].getCurrentAmmo() > 0 || reloadingPercentage >= 1.0)
	{
		reloadingProgressBar->update(1.0);
	}
	else
	{
		reloadingProgressBar->update(reloadingPercentage);
	}
}

void Game::GraphicsManager::Interface::draw(Game* game)
{
	int actionXPosition = 5;
	for (auto action : actions)
	{
		if (action.second > 1)
		{
			actionText.setString(action.first.first + " x" + toString(action.second));
		}
		else
		{
			actionText.setString(action.first.first);
		}
		actionText.setPosition(5, float(actionXPosition));

		game->window->draw(actionText);

		actionXPosition += 30;
	}

	string bulletText = toString(game->allPlayerWeapon[game->currentWeaponPointer].getCurrentAmmo());
	bulletText += "/";
	bulletText += toString(game->allPlayerWeapon[game->currentWeaponPointer].getCountBullets());
	bulletCount.setString(bulletText);
	bulletCount.setPosition(WINDOW_LENGTH - bulletCount.getGlobalBounds().width - 10, WINDOW_HIGH - 60 - 10);
	game->window->draw(bulletCount);

	HPSprite.setPosition(110, 645);
	game->window->draw(HPSprite);
	HPText.setString(toString(game->playerObject.getHealthPoints()));
	HPText.setPosition(100 - HPText.getGlobalBounds().width, 630);
	game->window->draw(HPText);

	armorSprite.setPosition(280, 645);
	game->window->draw(armorSprite);
	armorText.setString(toString(game->playerObject.armor));
	armorText.setPosition(270 - armorText.getGlobalBounds().width, 630);
	game->window->draw(armorText);

	weaponInconPointer->setPosition(WINDOW_LENGTH - 10 - INTERFACE_WEAPON_LENGTH, WINDOW_HIGH - 60 - INTERFACE_WEAPON_HIGH);
	game->window->draw(*weaponInconPointer);
	// todo if reloading

	grenadeSprite.setPosition(WINDOW_LENGTH - INTERFACE_SPRITE_LENGTH - 10, WINDOW_HIGH - 130 - INTERFACE_SPRITE_HIGH);
	game->window->draw(grenadeSprite);
	grenadeText.setString("5"); // todo
	grenadeText.setPosition(WINDOW_LENGTH - INTERFACE_SPRITE_LENGTH - 15 - grenadeText.getGlobalBounds().width, WINDOW_HIGH - 147 - INTERFACE_SPRITE_HIGH);
	game->window->draw(grenadeText);

	reloadingProgressBar->draw(game->window);
}
