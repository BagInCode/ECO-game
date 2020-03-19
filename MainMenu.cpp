#include "MainMenu.h"

#include <random>
#include <time.h>

MainMenu::MainMenu()
{
	timer = 0;

	init();

	newGame = new Button(WINDOW_LENGTH / 2 - 200, 50, 400, 100, font, "NEW GAME", Color(255, 255, 255), Color(189, 189, 189), Color(117, 117, 117));
	newGame->setTextSize(50);
	newGame->setTextColor(Color(213, 0, 0));
	newGame->setTextThickness(2);

	continueGame = new Button(WINDOW_LENGTH / 2 - 200, 200, 400, 100, font, "CONTINUE", Color(255, 255, 255), Color(189, 189, 189), Color(117, 117, 117));
	continueGame->setTextSize(50);
	continueGame->setTextColor(Color(213, 0, 0));
	continueGame->setTextThickness(2);

	settings = new Button(WINDOW_LENGTH / 2 - 200, 350, 400, 100, font, "SETTINGS", Color(255, 255, 255), Color(189, 189, 189), Color(117, 117, 117));
	settings->setTextSize(50);
	settings->setTextColor(Color(213, 0, 0));
	settings->setTextThickness(2);

	quit = new Button(WINDOW_LENGTH / 2 - 200, 500, 400, 100, font, "QUIT", Color(255, 255, 255), Color(189, 189, 189), Color(117, 117, 117));
	quit->setTextSize(50);
	quit->setTextColor(Color(213, 0, 0));
	quit->setTextThickness(2);
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
	font.loadFromFile(ROBO_REGULAR_FILE_PATH);
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
	mousePosition.x *= float(WINDOW_LENGTH) / float(window.getSize().x);
	mousePosition.y *= float(WINDOW_HIGH) / float(window.getSize().y);


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
		Game game;

		if (game.loadGame(window))
		{
			game.process(window);
		}
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
	window.clear(Color::Black);

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