#include "GameGraphicsManagerInterface.h"

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

void Game::GraphicsManager::Interface::update(double timer)
{
	for (int i = int(actions.size()) - 1; i >= 0; i--)
	{
		actions[i].first.second -= timer / 1000.0;
		if (actions[i].first.second < 0)
		{
			actions.erase(actions.begin() + i);
		}
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
		actionText.setPosition(5, actionXPosition);

		game->window->draw(actionText);

		actionXPosition += 30;
	}

	string bulletText = toString(game->allPlayerWeapon[game->currentWeaponPointer].getCurrentAmmo());
	bulletText += "/";
	bulletText += toString(game->allPlayerWeapon[game->currentWeaponPointer].getCountBullets());
	bulletCount.setString(bulletText);
	bulletCount.setPosition(WINDOW_LENGTH - bulletCount.getGlobalBounds().width - 10, WINDOW_HIGH - 60 - 10);
	game->window->draw(bulletCount);

}
