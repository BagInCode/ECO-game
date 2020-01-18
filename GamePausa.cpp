#include "GamePausa.h"

GamePausa::GamePausa()
{
	haveFocus = 1;
	continueGame = 0;

	font.loadFromFile("D:/ECO Game/ECO Game/Fonts/SourceSansPro-Black.ttf");

	continueGameRutton = new Button(WINDOW_LENGTH / 2 - 300, 250, 600, 150, font, "CONTINUE GAME", Color(0, 75, 75), Color(0, 150, 150), Color(0, 225, 225));
	continueGameRutton->setTextSize(72);

	backToMenuButton = new Button(WINDOW_LENGTH / 2 - 300, 450, 600, 150, font, "BACK TO MENU", Color(0, 75, 75), Color(0, 150, 150), Color(0, 225, 225));
	backToMenuButton->setTextSize(72);

	pausaText.setFont(font);
	pausaText.setString("PAUSA");
	pausaText.setFillColor(Color::White);
	pausaText.setOutlineThickness(5);
	pausaText.setOutlineColor(Color::Black);
	pausaText.setCharacterSize(200);
	pausaText.setPosition(WINDOW_LENGTH / 2.0 - pausaText.getGlobalBounds().width / 2.0, 0);
}

GamePausa::~GamePausa()
{
	delete backToMenuButton;
}

bool GamePausa::process(RenderWindow& window)
{
	/*
		return false if want back to menu (gameOver = 1 in Game class)	
	*/
	screenTexture.create(window.getSize().x, window.getSize().y);
	screenTexture.update(window);
	screenSprite.setTexture(screenTexture);
	screenSprite.setScale(
		double(WINDOW_LENGTH) / screenSprite.getGlobalBounds().width,
		double(WINDOW_HIGH) / screenSprite.getGlobalBounds().height
		);
	screenSprite.setPosition(0, 0);

	while (window.isOpen())
	{
		timer += clock.getElapsedTime().asMicroseconds() / 1000.0;
		clock.restart();

		if (window.pollEvent(event))
		{
			if (!switchEvent(event, window))
			{
				return false;
			}
		}

		if (continueGame == 1)
		{
			return true;
		}

		if (timer > MILISECONDS_PER_FRAME)
		{
			draw(window);

			timer = 0;
		}
	}


	return false;
}

bool GamePausa::switchEvent(Event event, RenderWindow &window)
{
	/*
		return false when want to return to the menu
	*/

	if (event.type == Event::Closed)
	{
		window.close();
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

	if (event.type == Event::KeyPressed)
	{
		if (event.key.code == Keyboard::Escape)
		{
			continueGame = 1;
		}
	}

	Vector2f mousePosition(Mouse::getPosition(window));
	mousePosition.x *= double(WINDOW_LENGTH) / double(window.getSize().x);
	mousePosition.y *= double(WINDOW_HIGH) / double(window.getSize().y);

	backToMenuButton->updateState(mousePosition);
	continueGameRutton->updateState(mousePosition);

	if (continueGameRutton->isPressed())
	{
		continueGame = 1;
	}

	if (backToMenuButton->isPressed())
	{
		return false;
	}

	return true;
}

void GamePausa::draw(RenderWindow& window)
{
	window.clear(Color::Red);
	window.draw(screenSprite);
	window.draw(pausaText);
	backToMenuButton->draw(window);
	continueGameRutton->draw(window);

	window.display();
}