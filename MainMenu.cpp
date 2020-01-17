#include "MainMenu.h"

MainMenu::MainMenu()
{
	haveFocus = 1;

	timer = 0;

	init();

	newGame = new Button(WINDOW_LENGTH / 2 - 200, 50, 400, 100, font, "NEW GAME", Color(75, 75, 0), Color(150, 150, 0), Color(225, 225, 0));
	newGame->setTextSize(48);

	continueGame = new Button(WINDOW_LENGTH / 2 - 200, 200, 400, 100, font, "CONTINUE", Color(75, 75, 0), Color(150, 150, 0), Color(225, 225, 0));
	continueGame->setTextSize(48);

	settings = new Button(WINDOW_LENGTH / 2 - 200, 350, 400, 100, font, "SETTINGS", Color(75, 75, 0), Color(150, 150, 0), Color(225, 225, 0));
	settings->setTextSize(48);

	quit = new Button(WINDOW_LENGTH / 2 - 200, 500, 400, 100, font, "QUIT", Color(75, 75, 0), Color(150, 150, 0), Color(225, 225, 0));
	quit->setTextSize(48);
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
	font.loadFromFile("D:/ECO Game/ECO Game/Fonts/SourceSansPro-Black.ttf");
}

bool MainMenu::switchEvent(Event event, RenderWindow &window)
{
	if (event.type == Event::Closed)
	{
		return false;
	}

	if (event.type == Event::LostFocus)
	{
		haveFocus = 0;

		return true;
	}
	if (event.type == Event::GainedFocus)
	{
		haveFocus = 1;
	}

	if (haveFocus == 0)
	{
		return true;
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

		clock.restart();
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
	if (haveFocus == 0)
	{
		return;
	}

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