#pragma once

#include "MainMenu.h"

class MainMenu::Settings
{
	Font* font;
	Text moveWText, moveSText, moveAText, moveDText;
	Text grenadeGText, interactEText, minimapMText, pausaEscText;

	Button* exitButton;

	Event event;
	Clock clock;
	double timer;

	int toProcess;

	void switchEvent(Event event, RenderWindow &window);
	void draw(RenderWindow& window);

public:

	Settings(Font* font);
	~Settings();

	void process(RenderWindow& window);

};