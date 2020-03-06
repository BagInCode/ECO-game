#include "GameGraphicsManager.h"

class Game::GraphicsManager::Interface
{
private:

	string toString(int val);

public:

	Texture InterfaceTexture;
	Sprite HPSprite, armorSprite, grenadeSprite;
	Sprite pistolSprite, shotgunSprite, AKSprite, minigunSprite, sniperSprite, *weaponInconPointer;
	Text HPText, armorText, grenadeText;

	Font font;

	vector <pair<pair<string, double>, int> > actions; //{text, duration, count}
	Text actionText;

	Text bulletCount;


	void initComponents();

	void addAction(string text, double duration);

	void update(Game* game, double timer);
	void draw(Game* game);
};