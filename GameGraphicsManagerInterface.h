#include "GameGraphicsManager.h"

class Game::GraphicsManager::Interface
{
private:

	string toString(int val);

public:

	Font font;

	vector <pair<pair<string, double>, int> > actions; //{text, duration, count}
	Text actionText;

	Text bulletCount;


	void initComponents();

	void addAction(string text, double duration);

	void update(double timer);
	void draw(Game* game);
};