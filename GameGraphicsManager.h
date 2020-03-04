#pragma once

#include "Game.h"

class Game::GraphicsManager
{
public:

	class Interface;

	Texture environmentTexture, temp, temp1, temp2, temp3;
	Sprite groundSprite, storageSprite, bulletSprite,* playerSprite, enemySprite, treeSprite, granadeSprite[4];
	Sprite playerPistolSprite, playerShotgunSprite, playerRifleSprite, playerMachinGunSprite, playerSniperRifleSprite;

	Texture minimapTexture;
	Sprite minimapActiveGroundSprite, minimapActiveHouseSprite, minimapActiveTreeSprite, minimapPlayerSprite, minimapEnemySprite;
	Sprite minimapInvisibleSprite, minimapInactiveGroundSprite, minimapInactiveHouseSprite, minimapInactiveTreeSprite;

	int isMinimapDrawing;

	Interface* interface;


	GraphicsManager();
	~GraphicsManager();

	void update(double timer);

	void initComponents();
	bool loadSprites();
	void draw(Game* game);
	void drawPicture(Game* game);
	void drawMinimap(Game* game);
};