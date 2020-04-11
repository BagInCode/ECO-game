#pragma once

#include "MainMenu.h"
#include "GlobalVariable.h"

class MainMenu::Settings
{
	Font* font;
	Text moveWText, moveSText, moveAText, moveDText;
	Text grenadeGText, interactEText, minimapMText, pausaEscText;

	Button* exitButton;
	Button* levelButton;

	Event event;
	Clock clock;
	double timer;

	int toProcess;

	void switchEvent(Event event, RenderWindow &window);
	void draw(RenderWindow& window);

	string toString(int val);
public:

	Settings(Font* font);
	~Settings();

	void process(RenderWindow& window);

};