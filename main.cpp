#include "Game.h"

using namespace std;
using namespace sf;

Game GameObject;

int main()
{
	RenderWindow window(VideoMode(WINDOW_LENGTH, WINDOW_HIGH), "ECO GAME");
	window.setKeyRepeatEnabled(false);

	GameObject.game(window);

	return 0;
}