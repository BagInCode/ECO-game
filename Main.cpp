#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "MainMenu.h"

#include "Constants.db"

using namespace std;
using namespace sf;

const string WINDOW_NAME = "ECO game";

int main()
{
	// create window
	RenderWindow window(VideoMode(WINDOW_LENGTH, WINDOW_HIGH), WINDOW_NAME);

	// if you press and hold key - it give only one event KeyPressed (at the begin)
	window.setKeyRepeatEnabled(0);

	MainMenu menu;

	// play and have fun))
	menu.process(window);

	return 0;
}