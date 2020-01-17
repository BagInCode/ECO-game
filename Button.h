#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "Constants.db"

using namespace std;
using namespace sf;

enum BUTTON_STATE
{
	BUTTON_IDLE,
	BUTTON_HOVER,
	BUTTON_ACTIVE
};


class Button
{
private:

	pair<BUTTON_STATE, BUTTON_STATE> buttonState; // current state - first, previous state - second

	RectangleShape shape;
	Font font;
	Text text;

	Color idleColor;
	Color hoverColor;
	Color activeColor;

public:

	Button(float x, float y, float width, float height, Font font, string text,
		Color idleColor, Color hoverColor, Color activeColor);
	~Button();

	void setTextSize(int textSize);
	void setTextColor(Color textColor);
	void setIdleColor(Color idleColor);
	void setHoverColor(Color hoverColor);
	void setActiveColor(Color activeColor);

	bool isPressed();

	void updateState(Vector2f mousePosition);
	void draw(RenderWindow& window);

};