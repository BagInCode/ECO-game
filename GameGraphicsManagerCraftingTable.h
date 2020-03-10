#pragma once

#include "GameGraphicsManager.h"
#include "ProgressBar.h"
#include "Button.h"


class Game::GraphicsManager::CraftingTable
{
public:

	ProgressBar* reloadProgressBar, *accuracyProgressBar, *damageProgressBar, *gainingAmmoProgressBar;
	Button* pistolButton, *shotgunButton, *AKButton, *minigunButton, *sniperButton;

	Texture weaponTextures;
	Sprite pistolSprite, shotgunSprite, AKSprite, minigunSprite, sniperSprite, *weaponInconPointer;

	Font * font;

	CraftingTable();
	~CraftingTable();


	void initComponents(Game* game);

	void update(Game* game);

	void open(Game* game);
	void draw(Game* game);

};