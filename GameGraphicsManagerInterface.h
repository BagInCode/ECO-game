#include "GameGraphicsManager.h"

class Game::GraphicsManager::Interface
{
private:

	string toString(int val);

public:

	Texture InterfaceTexture;
	Sprite HPSprite, armorSprite, granadeSprite;
	Sprite PistolSprite, DoubleSprite, AKSprite, MinigunSprite, SniperSprite;
	Text HPText, armorText, granadeText;

	Font font;

	vector <pair<pair<string, double>, int> > actions; //{text, duration, count}
	Text actionText;

	Text bulletCount;


	void initComponents();

	void addAction(string text, double duration);

	void update(double timer);
	void draw(Game* game);
};