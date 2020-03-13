#pragma once

#include "Game.h"

class Game::GraphicsManager
{
public:

	class Interface;
	class Minimap;
	class CraftingTable;

	Texture environmentTexture, craftingTableTexture;
	Sprite groundSprite, storageSprite[2], bulletSprite, *playerSprite, enemySprite, treeSprite, grenadeSprite[4], craftingTableSprite;
	Sprite playerPistolSprite, playerShotgunSprite, playerRifleSprite, playerMachinGunSprite, playerSniperRifleSprite;

	Font storageFont;

	int drawSwitcher;

	Interface* interface;
	Minimap* minimap;
	CraftingTable* craftingTable;


	GraphicsManager();
	~GraphicsManager();

	void update(Game *game, double timer);

	void initComponents(Game* game);
	bool loadSprites();
	void draw(Game* game, WaveManager* waveManager);
	void drawPicture(Game* game);
};