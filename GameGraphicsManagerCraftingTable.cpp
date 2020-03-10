#include "GameGraphicsManagerCraftingTable.h"
#include "Game.h"

Game::GraphicsManager::CraftingTable::CraftingTable()
{
	reloadProgressBar = new ProgressBar(700, 300, 300, 30, 3, 1);
	accuracyProgressBar = new ProgressBar(700, 400, 300, 30, 3, 1);
	damageProgressBar = new ProgressBar(700, 500, 300, 30, 3, 1);
	gainingAmmoProgressBar = new ProgressBar(700, 600, 300, 30, 3, 1);

	font = new Font;
	font->loadFromFile("Fonts\\CraftingTable.ttf");

	pistolButton = new Button(50, 50, 270, 80, *font, " ", Color::Blue, Color::Magenta, Color::Green);
	shotgunButton = new Button(50, 150, 270, 80, *font, " ", Color::Blue, Color::Magenta, Color::Green);
	AKButton = new Button(50, 250, 270, 80, *font, " ", Color::Blue, Color::Magenta, Color::Green);
	minigunButton = new Button(50, 350, 270, 80, *font, " ", Color::Blue, Color::Magenta, Color::Green);
	sniperButton = new Button(50, 450, 270, 80, *font, " ", Color::Blue, Color::Magenta, Color::Green);
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

}

void Game::GraphicsManager::CraftingTable::update(Game* game)
{
	Vector2f mousePosition(Mouse::getPosition(*(game->window)));

	mousePosition.x *= float(WINDOW_LENGTH) / float(game->window->getSize().x);
	mousePosition.y *= float(WINDOW_HIGH) / float(game->window->getSize().y);

	pistolButton->updateState(mousePosition);
	shotgunButton->updateState(mousePosition);
	AKButton->updateState(mousePosition);
	minigunButton->updateState(mousePosition);
	sniperButton->updateState(mousePosition);

	if (pistolButton->isPressed())
	{
		weaponInconPointer = &pistolSprite;
	}
	if (shotgunButton->isPressed())
	{
		weaponInconPointer = &shotgunSprite;
	}
	if (AKButton->isPressed())
	{
		weaponInconPointer = &AKSprite;
	}
	if (minigunButton->isPressed())
	{
		weaponInconPointer = &minigunSprite;
	}
	if (sniperButton->isPressed())
	{
		weaponInconPointer = &sniperSprite;
	}

	if (weaponInconPointer != nullptr)
	{
		weaponInconPointer->setPosition(700, 200);
	}
}

void Game::GraphicsManager::CraftingTable::open(Game* game)
{

}

void Game::GraphicsManager::CraftingTable::draw(Game* game)
{
	game->window->clear(Color::Cyan);

	reloadProgressBar->draw(game->window);
	accuracyProgressBar->draw(game->window);
	damageProgressBar->draw(game->window);
	gainingAmmoProgressBar->draw(game->window);

	pistolButton->draw(*(game->window));
	shotgunButton->draw(*(game->window));
	AKButton->draw(*(game->window));
	minigunButton->draw(*(game->window));
	sniperButton->draw(*(game->window));

	if (weaponInconPointer != nullptr)
	{
		game->window->draw(*weaponInconPointer);
	}
}