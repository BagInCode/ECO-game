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
	/*
	This button is not very flexible and require attention
	be accurate using it
	*/

private:

	pair<BUTTON_STATE, BUTTON_STATE> buttonState;

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
	void setTextColor(Color color);
	void setTextThickness(int thicknessSize);

	bool isPressed();

	void updateState(Vector2f mousePosition);
	void draw(RenderWindow& window);

};