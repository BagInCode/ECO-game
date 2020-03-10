#pragma once

#include "GameGraphicsManager.h"

class Game::GraphicsManager::Minimap
{
public:

	Texture minimapTexture, craftingTableTexture;
	Sprite activeGroundSprite, activeHouseSprite, activeTreeSprite, playerSprite, enemySprite, activeCraftingTableSprite;
	Sprite invisibleSprite, inactiveGroundSprite, inactiveHouseSprite, inactiveTreeSprite, inactiveCraftingTableSprite;

	bool visionMap[FIELD_SIZE][FIELD_SIZE];

	void update(Game* game);
	void updateVision(Game* game);
	bool isVisible(int playerX, int playerY, int x, int y);
	void initComponents();
	void loadSprites();
	void draw(Game* game);

};