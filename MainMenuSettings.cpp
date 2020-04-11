#include "MainMenuSettings.h"



MainMenu::Settings::Settings(Font* font)
{
	this->font = font;

	exitButton = new Button(450, 560, 400, 100, *font, "Back to menu", Color(255, 255, 255), Color(189, 189, 189), Color(117, 117, 117));
	exitButton->setTextSize(60);
	exitButton->setTextColor(Color(213, 0, 0));
	exitButton->setTextThickness(2);

	levelButton = new Button(450, 450, 400, 100, *font, "Level " + toString(GlobalVariable::gameLevel + 1), Color(255, 255, 255), Color(189, 189, 189), Color(117, 117, 117));
	levelButton->setTextSize(60);
	levelButton->setTextColor(Color(213, 0, 0));
	levelButton->setTextThickness(2);

	moveWText.setString("W - move up");
	moveWText.setFont(*font);
	moveWText.setCharacterSize(40);
	moveWText.setFillColor(Color::White);
	moveWText.setOutlineThickness(1);
	moveWText.setOutlineColor(Color::Red);
	moveWText.setPosition(450, 10);

	moveSText.setString("S - move down");
	moveSText.setFont(*font);
	moveSText.setCharacterSize(40);
	moveSText.setFillColor(Color::White);
	moveSText.setOutlineThickness(1);
	moveSText.setOutlineColor(Color::Red);
	moveSText.setPosition(450, 60);

	moveAText.setString("A - move left");
	moveAText.setFont(*font);
	moveAText.setCharacterSize(40);
	moveAText.setFillColor(Color::White);
	moveAText.setOutlineThickness(1);
	moveAText.setOutlineColor(Color::Red);
	moveAText.setPosition(450, 110);

	moveDText.setString("D - move right");
	moveDText.setFont(*font);
	moveDText.setCharacterSize(40);
	moveDText.setFillColor(Color::White);
	moveDText.setOutlineThickness(1);
	moveDText.setOutlineColor(Color::Red);
	moveDText.setPosition(450, 160);

	grenadeGText.setString("G - throw grenade");
	grenadeGText.setFont(*font);
	grenadeGText.setCharacterSize(40);
	grenadeGText.setFillColor(Color::White);
	grenadeGText.setOutlineThickness(1);
	grenadeGText.setOutlineColor(Color::Red);
	grenadeGText.setPosition(450, 210);

	interactEText.setString("E - interact with object");
	interactEText.setFont(*font);
	interactEText.setCharacterSize(40);
	interactEText.setFillColor(Color::White);
	interactEText.setOutlineThickness(1);
	interactEText.setOutlineColor(Color::Red);
	interactEText.setPosition(450, 260);

	minimapMText.setString("M - show minimap");
	minimapMText.setFont(*font);
	minimapMText.setCharacterSize(40);
	minimapMText.setFillColor(Color::White);
	minimapMText.setOutlineThickness(1);
	minimapMText.setOutlineColor(Color::Red);
	minimapMText.setPosition(450, 310);

	pausaEscText.setString("Esc - pause");
	pausaEscText.setFont(*font);
	pausaEscText.setCharacterSize(40);
	pausaEscText.setFillColor(Color::White);
	pausaEscText.setOutlineThickness(1);
	pausaEscText.setOutlineColor(Color::Red);
	pausaEscText.setPosition(450, 360);

	toProcess = 0;
}

MainMenu::Settings::~Settings()
{
	delete exitButton;
	delete levelButton;
}

void MainMenu::Settings::switchEvent(Event event, RenderWindow &window)
{
	if (event.type == Event::Closed)
	{
		window.close();
		toProcess = 0;
	}

	Vector2f mousePosition(Mouse::getPosition(window));
	mousePosition.x *= float(WINDOW_LENGTH) / float(window.getSize().x);
	mousePosition.y *= float(WINDOW_HIGH) / float(window.getSize().y);
	
	exitButton->updateState(mousePosition);

	if (exitButton->isPressed())
	{
		toProcess = 0;
	}

	levelButton->updateState(mousePosition);

	if (levelButton->isPressed())
	{
		GlobalVariable::gameLevel = (GlobalVariable::gameLevel + 1) % 3;

		levelButton->setText("Level " + toString(GlobalVariable::gameLevel + 1));
	}
}

void MainMenu::Settings::draw(RenderWindow &window)
{
	window.clear(Color::Black);

	exitButton->draw(window);
	levelButton->draw(window);

	window.draw(moveWText);
	window.draw(moveSText);
	window.draw(moveAText);
	window.draw(moveDText);
	window.draw(grenadeGText);
	window.draw(interactEText);
	window.draw(minimapMText);
	window.draw(pausaEscText);


	window.display();
}

void MainMenu::Settings::process(RenderWindow& window)
{
	clock.restart();
	toProcess = 1;
	timer = 0;

	while (toProcess)
	{
		timer += clock.getElapsedTime().asMicroseconds() / 1000.0;
		clock.restart();

		if (window.pollEvent(event))
		{
			switchEvent(event, window);
		}

		if (timer > MILISECONDS_PER_FRAME)
		{
			draw(window);

			timer = 0.0;
		}
	}
}

string MainMenu::Settings::toString(int val)
{
	/*
	* function of converting positiove integer value to string
	*
	* @param val - positive integer value
	*
	* @return string form of this value
	*/

	// if value is 0
	if (val == 0)
	{
		// return string with 0
		return "0";
	}

	// create string for result
	string res;

	// while value grethe than zero
	while (val > 0)
	{
		// add to result last digit
		res += char('0' + val % 10);

		// remove last digit from value
		val /= 10;
	}

	// reverse string
	reverse(res.begin(), res.end());

	return res;
}
