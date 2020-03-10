#include "GameGraphicsManagerCraftingTable.h"
#include "Game.h"

Game::GraphicsManager::CraftingTable::CraftingTable()
{
	font = new Font;
	font->loadFromFile("Fonts\\CraftingTable.ttf");

	pistolButton = new Button(40, 130, 335, 100, *font, " ", Color(0, 0, 0, 0), Color(140, 205, 190, 200), Color(100, 165, 150, 220));
	shotgunButton = new Button(40, 240, 335, 100, *font, " ", Color(0, 0, 0, 0), Color(140, 205, 190, 200), Color(100, 165, 150, 220));
	AKButton = new Button(40, 350, 335, 100, *font, " ", Color(0, 0, 0, 0), Color(140, 205, 190, 200), Color(100, 165, 150, 220));
	minigunButton = new Button(40, 460, 335, 100, *font, " ", Color(0, 0, 0, 0), Color(140, 205, 190, 200), Color(100, 165, 150, 220));
	sniperButton = new Button(40, 570, 335, 100, *font, " ", Color(0, 0, 0, 0), Color(140, 205, 190, 200), Color(100, 165, 150, 220));

	reloadProgressBar = new ProgressBar(700, 300, 300, 20, 3, 1);
	accuracyProgressBar = new ProgressBar(700, 400, 300, 20, 3, 1);
	damageProgressBar = new ProgressBar(700, 500, 300, 20, 3, 1);
	gainingAmmoProgressBar = new ProgressBar(700, 600, 300, 20, 3, 1);

	reloadButton = new Button(420, 270, 250, 80, *font, "Reloading", Color(0, 0, 0, 0), Color(140, 205, 190, 100), Color(140, 205, 190, 200));
	accuracyButton = new Button(420, 365, 250, 80, *font, "Accuracy", Color(0, 0, 0, 0), Color(140, 205, 190, 100), Color(140, 205, 190, 200));
	damageButton = new Button(420, 465, 250, 80, *font, "Damage", Color(0, 0, 0, 0), Color(140, 205, 190, 100), Color(140, 205, 190, 200));
	gainingAmmoButton = new Button(420, 560, 250, 80, *font, "Ammo loot", Color(0, 0, 0, 0), Color(140, 205, 190, 100), Color(140, 205, 190, 200));

	improveButton = new Button(420, 180, 250, 80, *font, "Improve", Color(0, 0, 0, 0), Color(140, 205, 190, 100), Color(140, 205, 190, 200));
}

Game::GraphicsManager::CraftingTable::~CraftingTable()
{
	delete reloadProgressBar;
	delete accuracyProgressBar;
	delete damageProgressBar;
	delete gainingAmmoProgressBar;

	delete font;

	delete pistolButton;
	delete shotgunButton;
	delete AKButton;
	delete minigunButton;
	delete sniperButton;

	delete reloadButton;
	delete accuracyButton;
	delete damageButton;
	delete gainingAmmoButton;

	delete improveButton;
}

string Game::GraphicsManager::CraftingTable::toString(int val)
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

void Game::GraphicsManager::CraftingTable::initComponents(Game* game)
{
	reloadProgressBar->setWaitColor(Color::White);
	reloadProgressBar->setDrawPotential(1);
	reloadProgressBar->setPotentialPercentage(0.0);
	reloadProgressBar->update(0.0);

	accuracyProgressBar->setWaitColor(Color::White);
	accuracyProgressBar->setDrawPotential(1);
	accuracyProgressBar->setPotentialPercentage(0.0);
	accuracyProgressBar->update(0.0);

	damageProgressBar->setWaitColor(Color::White);
	damageProgressBar->setDrawPotential(1);
	damageProgressBar->setPotentialPercentage(0.0);
	damageProgressBar->update(0.0);

	gainingAmmoProgressBar->setWaitColor(Color::White);
	gainingAmmoProgressBar->setDrawPotential(1);
	gainingAmmoProgressBar->setPotentialPercentage(0.0);
	gainingAmmoProgressBar->update(0.0);


	weaponTextures.loadFromFile("Textures\\craftingTableWeapons.png");

	pistolSprite.setTexture(weaponTextures);
	pistolSprite.setTextureRect(IntRect(PISTOL_INTERFACE_POSITION_LEFT, PISTOL_INTERFACE_POSITION_TOP, INTERFACE_WEAPON_LENGTH, INTERFACE_WEAPON_HIGH));
	pistolButton->setBackgroundImage(pistolSprite);

	shotgunSprite.setTexture(weaponTextures);
	shotgunSprite.setTextureRect(IntRect(SHOTGUN_INTERFACE_POSITION_LEFT, SHOTGUN_INTERFACE_POSITION_TOP, INTERFACE_WEAPON_LENGTH, INTERFACE_WEAPON_HIGH));
	shotgunButton->setBackgroundImage(shotgunSprite);

	AKSprite.setTexture(weaponTextures);
	AKSprite.setTextureRect(IntRect(AK_INTERFACE_POSITION_LEFT, AK_INTERFACE_POSITION_TOP, INTERFACE_WEAPON_LENGTH, INTERFACE_WEAPON_HIGH));
	AKButton->setBackgroundImage(AKSprite);

	minigunSprite.setTexture(weaponTextures);
	minigunSprite.setTextureRect(IntRect(MINIGUN_INTERFACE_POSITION_LEFT, MINIGUN_INTERFACE_POSITION_TOP, INTERFACE_WEAPON_LENGTH, INTERFACE_WEAPON_HIGH));
	minigunButton->setBackgroundImage(minigunSprite);

	sniperSprite.setTexture(weaponTextures);
	sniperSprite.setTextureRect(IntRect(SNIPER_INTERFACE_POSITION_LEFT, SNIPER_INTERFACE_POSITION_TOP, INTERFACE_WEAPON_LENGTH, INTERFACE_WEAPON_HIGH));
	sniperButton->setBackgroundImage(sniperSprite);

	weaponInconPointer = nullptr;

	engramPointsText.setFont(*font);
	engramPointsText.setCharacterSize(72);
	engramPointsText.setFillColor(Color::Black);
	engramPointsText.setOutlineThickness(2);
	engramPointsText.setOutlineColor(Color::White);
	engramPointsText.setString("Engram points: " + toString(game->playerObject.getEngramPoints()));
	engramPointsText.setPosition(15, 15);

	reloadButton->setTextSpacing(15);
	reloadButton->setTextColor(Color::Black);
	reloadButton->setTextSize(40);
	reloadButton->setTextThicknessColor(Color::White);
	reloadButton->setTextThickness(2);

	accuracyButton->setTextSpacing(15);
	accuracyButton->setTextColor(Color::Black);
	accuracyButton->setTextSize(40);
	accuracyButton->setTextThicknessColor(Color::White);
	accuracyButton->setTextThickness(2);

	damageButton->setTextSpacing(15);
	damageButton->setTextColor(Color::Black);
	damageButton->setTextSize(40);
	damageButton->setTextThicknessColor(Color::White);
	damageButton->setTextThickness(2);

	gainingAmmoButton->setTextSpacing(15);
	gainingAmmoButton->setTextColor(Color::Black);
	gainingAmmoButton->setTextSize(40);
	gainingAmmoButton->setTextThicknessColor(Color::White);
	gainingAmmoButton->setTextThickness(2);

	improveButton->setTextSpacing(20);
	improveButton->setTextColor(Color::Black);
	improveButton->setTextSize(60);
	improveButton->setTextThicknessColor(Color::White);
	improveButton->setTextThickness(2);
}

void Game::GraphicsManager::CraftingTable::update(Game* game)
{
	Vector2f mousePosition(Mouse::getPosition(*(game->window)));

	mousePosition.x *= float(WINDOW_LENGTH) / float(game->window->getSize().x);
	mousePosition.y *= float(WINDOW_HIGH) / float(game->window->getSize().y);

	engramPointsText.setString("Engram points: " + toString(game->playerObject.getEngramPoints()));

	pistolButton->updateState(mousePosition);
	shotgunButton->updateState(mousePosition);
	AKButton->updateState(mousePosition);
	minigunButton->updateState(mousePosition);
	sniperButton->updateState(mousePosition);

	if (pistolButton->isPressed())
	{
		weaponInconPointer = &pistolSprite;
		weaponIndex = 0;
	}
	if (shotgunButton->isPressed())
	{
		weaponInconPointer = &shotgunSprite;
		weaponIndex = 1;
	}
	if (AKButton->isPressed())
	{
		weaponInconPointer = &AKSprite;
		weaponIndex = 2;
	}
	if (minigunButton->isPressed())
	{
		weaponInconPointer = &minigunSprite;
		weaponIndex = 3;
	}
	if (sniperButton->isPressed())
	{
		weaponInconPointer = &sniperSprite;
		weaponIndex = 4;
	}

	if (weaponInconPointer != nullptr)
	{
		weaponInconPointer->setPosition(720, 210);
		weaponInconPointer->setScale(2, 2);

		reloadProgressBar->update(float(game->allPlayerWeapon[weaponIndex].reloadEngrams) / 5.0);
		accuracyProgressBar->update(float(game->allPlayerWeapon[weaponIndex].accuracyEngrams) / 5.0);
		damageProgressBar->update(float(game->allPlayerWeapon[weaponIndex].damageEngrams) / 5.0);
		gainingAmmoProgressBar->update(float(game->allPlayerWeapon[weaponIndex].gainingAmmoEngrams) / 5.0);

		reloadButton->updateState(mousePosition);
		accuracyButton->updateState(mousePosition);
		damageButton->updateState(mousePosition);
		gainingAmmoButton->updateState(mousePosition);

		if (reloadButton->isPressed())
		{
			skillIndex = 0;
		}
		if (accuracyButton->isPressed())
		{
			skillIndex = 1;
		}
		if (damageButton->isPressed())
		{
			skillIndex = 2;
		}
		if (gainingAmmoButton->isPressed())
		{
			skillIndex = 3;
		}

		reloadProgressBar->setPotentialPercentage(0.0);
		accuracyProgressBar->setPotentialPercentage(0.0);
		damageProgressBar->setPotentialPercentage(0.0);
		gainingAmmoProgressBar->setPotentialPercentage(0.0);

		if (skillIndex == 0)
		{
			reloadProgressBar->setPotentialPercentage(0.2);
		}
		else if (skillIndex == 1)
		{
			accuracyProgressBar->setPotentialPercentage(0.2);
		}
		else if (skillIndex == 2)
		{
			damageProgressBar->setPotentialPercentage(0.2);
		}
		else if (skillIndex == 3)
		{
			gainingAmmoProgressBar->setPotentialPercentage(0.2);
		}

		if (skillIndex != -1)
		{
			improveButton->updateState(mousePosition);

			if (improveButton->isPressed() && game->playerObject.getEngramPoints() > 0)
			{
				if (skillIndex == 0)
				{
					if (game->allPlayerWeapon[weaponIndex].reloadEngrams < 5)
					{
						game->allPlayerWeapon[weaponIndex].reloadEngrams++;
						game->allPlayerWeapon[weaponIndex].improveReloading(0.8);
						game->playerObject.decrEngramPoints(1);
					}
				}
				else if (skillIndex == 1)
				{
					if (game->allPlayerWeapon[weaponIndex].accuracyEngrams < 5)
					{
						game->allPlayerWeapon[weaponIndex].accuracyEngrams++;
						game->allPlayerWeapon[weaponIndex].improveAccuracy(0.8);
						game->playerObject.decrEngramPoints(1);
					}
				}
				else if (skillIndex == 2)
				{
					if (game->allPlayerWeapon[weaponIndex].damageEngrams < 5)
					{
						game->allPlayerWeapon[weaponIndex].damageEngrams++;
						game->allPlayerWeapon[weaponIndex].improveDamage(5);
						game->playerObject.decrEngramPoints(1);
					}
				}
				else if (skillIndex == 3)
				{
					if (game->allPlayerWeapon[weaponIndex].gainingAmmoEngrams < 5)
					{
						game->allPlayerWeapon[weaponIndex].gainingAmmoEngrams++;
						game->allPlayerWeapon[weaponIndex].improveAmmoLoot();
						game->playerObject.decrEngramPoints(1);
					}
				}
			}
		}
	}
}

void Game::GraphicsManager::CraftingTable::open(Game* game)
{
	weaponInconPointer = nullptr;
	weaponIndex = -1;
	skillIndex = -1;
}

void Game::GraphicsManager::CraftingTable::draw(Game* game)
{
	game->window->clear(Color(190, 235, 220));

	game->window->draw(engramPointsText);

	pistolButton->draw(*(game->window));
	shotgunButton->draw(*(game->window));
	AKButton->draw(*(game->window));
	minigunButton->draw(*(game->window));
	sniperButton->draw(*(game->window));

	if (weaponInconPointer != nullptr)
	{
		game->window->draw(*weaponInconPointer);

		reloadProgressBar->draw(game->window);
		accuracyProgressBar->draw(game->window);
		damageProgressBar->draw(game->window);
		gainingAmmoProgressBar->draw(game->window);
	
		reloadButton->draw(*(game->window));
		accuracyButton->draw(*(game->window));
		damageButton->draw(*(game->window));
		gainingAmmoButton->draw(*(game->window));


		if (skillIndex != -1 && game->playerObject.getEngramPoints() > 0)
		{
			int engrams;
			if (skillIndex == 0)
			{
				engrams = game->allPlayerWeapon[weaponIndex].reloadEngrams;
			}
			else if (skillIndex == 1)
			{
				engrams = game->allPlayerWeapon[weaponIndex].accuracyEngrams;
			}
			else if (skillIndex == 2)
			{
				engrams = game->allPlayerWeapon[weaponIndex].damageEngrams;
			}
			else if (skillIndex == 3)
			{
				engrams = game->allPlayerWeapon[weaponIndex].gainingAmmoEngrams;
			}

			if (engrams != 5)
			{
				improveButton->draw(*(game->window));
			}
		}
	}
}