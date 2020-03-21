#pragma once

#include "GameGraphicsManager.h"
#include "ProgressBar.h"
#include "Button.h"


class Game::GraphicsManager::CraftingTable
{
public:

	Button* pistolButton, *shotgunButton, *AKButton, *minigunButton, *sniperButton;
	ProgressBar* reloadProgressBar, *accuracyProgressBar, *damageProgressBar, *gainingAmmoProgressBar;
	Button* reloadButton, *accuracyButton, *damageButton, *gainingAmmoButton;
	Button* improveButton;

	Texture weaponTextures;
	Sprite pistolSprite, shotgunSprite, AKSprite, minigunSprite, sniperSprite, *weaponInconPointer;

	Text engramPointsText, pressToExitText;

	int weaponIndex, skillIndex;

	Font * font;

	CraftingTable();
	~CraftingTable();

	string toString(int val);

	void initComponents(Game* game);

	void update(Game* game);
	void improveWeapon(Game* game);

	void open(Game* game);
	void draw(Game* game);

};