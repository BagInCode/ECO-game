#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "Button.h"
#include "Constants.db"

using namespace std;
using namespace sf;

class ToggleBox
{
	vector <string> cases;
	int caseIndex;

	float positionX, positionY;
	float height, width;

	float pointerHeight, pointerWidth;

	RectangleShape mainShape;
	Texture pointerTexture;
	Button* leftPointer, *rightPointer;
	Text text;

public:

	ToggleBox(float x, float y, float width, float height, float pointerHeight, float pointerWidth, Texture pointerTexture, Font& font);
	~ToggleBox();

	void addCase(string txt);
	void setCaseIndex(int index);
	int getCaseIndex();

	void update(RenderWindow &window);
	void draw(RenderWindow &window);

};