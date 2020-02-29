#pragma once

#include "Game.h"



class Game::GraphicsManager
{
public:

	Texture environmentTexture;
	Sprite groundSprite, storageSprite, bulletSprite,* playerSprite, enemySprite, treeSprite;
	Sprite playerPistolSprite, playerShotgunSprite, playerRifleSprite, playerMachinGunSprite, playerSniperRifleSprite;

	Texture minimapTexture;
	Sprite minimapActiveGroundSprite, minimapActiveHouseSprite, minimapActiveTreeSprite, minimapPlayerSprite, minimapEnemySprite;
	Sprite minimapInvisibleSprite, minimapInactiveGroundSprite, minimapInactiveHouseSprite, minimapInactiveTreeSprite;

	int isMinimapDrawing;

	bool loadSprites();
	void drawPicture(Game* game);
	void drawMinimap(Game* game);
};