#pragma once
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Button.h"

#include "Constants.db"

#define MILISECONDS_PER_FRAME 20.0

class GamePausa
{
private:

	int haveFocus;
	int continueGame;

	Font font;
	Event event;

	Text pausaText;
	Button* backToMenuButton;
	Button* continueGameRutton;

	Texture screenTexture;
	Sprite screenSprite;

	Clock clock;
	double timer;

	bool switchEvent(Event event, RenderWindow &window);
	void draw(RenderWindow& window);

public:

	GamePausa();
	~GamePausa();

	bool process(RenderWindow& window);

};

