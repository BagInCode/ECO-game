#include "MainMenu.h"

MainMenu::MainMenu()
{
	timer = 0;

	init();

	newGame = new Button(WINDOW_LENGTH / 2 - 200, 50, 400, 100, font, "NEW GAME", Color(255, 255, 255), Color(189, 189, 189), Color(117, 117, 117));
	newGame->setTextSize(24);
	newGame->setTextColor(Color(213, 0, 0));

	continueGame = new Button(WINDOW_LENGTH / 2 - 200, 200, 400, 100, font, "CONTINUE", Color(255, 255, 255), Color(189, 189, 189), Color(117, 117, 117));
	continueGame->setTextSize(24);
	continueGame->setTextColor(Color(213, 0, 0));

	settings = new Button(WINDOW_LENGTH / 2 - 200, 350, 400, 100, font, "SETTINGS", Color(255, 255, 255), Color(189, 189, 189), Color(117, 117, 117));
	settings->setTextSize(24);
	settings->setTextColor(Color(213, 0, 0));

	quit = new Button(WINDOW_LENGTH / 2 - 200, 500, 400, 100, font, "QUIT", Color(255, 255, 255), Color(189, 189, 189), Color(117, 117, 117));
	quit->setTextSize(24);
	quit->setTextColor(Color(213, 0, 0));
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
	font.loadFromFile("E:/ECO Game/ECO Game/Fonts/Roboto-Regular.ttf");
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