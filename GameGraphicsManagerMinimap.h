#pragma once

#include "GameGraphicsManager.h"
#include <fstream>

class Game::GraphicsManager::Minimap
{
public:

	Texture minimapTexture, craftingTableTexture;
	Sprite activeGroundSprite, activeHouseSprite, activeTreeSprite, playerSprite, enemySprite, activeCraftingTableSprite;
	Sprite invisibleSprite, inactiveGroundSprite, inactiveHouseSprite, inactiveTreeSprite, inactiveCraftingTableSprite;

	int countVisibleSquares;

	bool visionMap[FIELD_SIZE][FIELD_SIZE];

	void update(Game* game);
	void updateVision(Game* game);

	bool isVisible(int playerX, int playerY, int x, int y);
	void initComponents();
	void loadSprites();
	void draw(Game* game);

	void load(vector < int >& minimapData);
	void safe(ofstream& out, int& safeOption, void(*updSafeOption)(int&, int));

	void clearGame();
};