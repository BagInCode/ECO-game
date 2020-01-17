#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Game.h"
#include "Button.h"

#include "Constants.db"

#define MILISECONDS_PER_FRAME 20.0

class MainMenu
{
private:

	Font font;
	Event event;

	Button* newGame;
	Button* continueGame;
	Button* settings;
	Button* quit;

	Clock clock;
	double timer;

	void init();
	bool switchEvent(Event event, RenderWindow &window);
	void draw(RenderWindow& window);

public:

	MainMenu();
	~MainMenu();

	bool process(RenderWindow& window);
};

