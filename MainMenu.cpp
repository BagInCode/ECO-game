#include "MainMenu.h"

MainMenu::MainMenu()
{
	timer = 0;

	init();

	newGame = new Button(WINDOW_LENGTH / 2 - 200, 50, 400, 100, font, "NEW GAME", Color(75, 75, 0), Color(150, 150, 0), Color(225, 225, 0));
	newGame->setTextSize(24);

	continueGame = new Button(WINDOW_LENGTH / 2 - 200, 200, 400, 100, font, "CONTINUE", Color(75, 75, 0), Color(150, 150, 0), Color(225, 225, 0));
	continueGame->setTextSize(24);

	settings = new Button(WINDOW_LENGTH / 2 - 200, 350, 400, 100, font, "SETTINGS", Color(75, 75, 0), Color(150, 150, 0), Color(225, 225, 0));
	settings->setTextSize(24);

	quit = new Button(WINDOW_LENGTH / 2 - 200, 500, 400, 100, font, "QUIT", Color(75, 75, 0), Color(150, 150, 0), Color(225, 225, 0));
	quit->setTextSize(24);
}

MainMenu::~MainMenu()
{
	delete newGame;
	delete continueGame;
	delete settings;
	delete quit;
}

void MainMenu::init()
{
	font.loadFromFile("D:/ECO Game/ECO Game/Fonts/Roboto-Regular.ttf");
}

bool MainMenu::switchEvent(Event event, RenderWindow &window)
{
	if (event.type == Event::Closed)
	{
		return false;
	}

	if (event.type == Event::LostFocus)
	{
		// todo to not redraw 

		return true;
	}
	if (event.type == Event::GainedFocus)
	{
		// todo to redraw again 
	}

	Vector2f mousePosition(Mouse::getPosition(window));
	mousePosition.x *= double(WINDOW_LENGTH) / double(window.getSize().x);
	mousePosition.y *= double(WINDOW_HIGH) / double(window.getSize().y);


	newGame->updateState(mousePosition);
	continueGame->updateState(mousePosition);
	settings->updateState(mousePosition);
	quit->updateState(mousePosition);

	if (newGame->isPressed())
	{
		Game game;

		game.process(window);
	}

	if (continueGame->isPressed())
	{
		// todo
	}

	if (settings->isPressed())
	{
		// todo
	}

	if (quit->isPressed())
	{
		window.close();
		exit(0);
	}

	return true;
}

void MainMenu::draw(RenderWindow& window)
{
	window.clear(Color::Cyan);

	newGame->draw(window);
	continueGame->draw(window);
	settings->draw(window);
	quit->draw(window);

	window.display();
}

bool MainMenu::process(RenderWindow& window)
{
	while (window.isOpen())
	{
		timer += clock.getElapsedTime().asMicroseconds() / 1000.0;
		clock.restart();

		if (window.pollEvent(event))
		{
			if (!switchEvent(event, window))
			{
				window.close();
			}
		}

		if (timer > MILISECONDS_PER_FRAME)
		{
			draw(window);

			timer = 0.0;
		}
	}

	return true;
}