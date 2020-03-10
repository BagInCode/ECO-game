#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "Constants.db"

using namespace std;
using namespace sf;

class ProgressBar
{
private:

	int width, height, borderSize;
	Color progressColor, waitColor, borderColor, potentialColor;
	RectangleShape progressRectangle, waitRectangle, borderRectangle, potentialRectangle;

	int drawWhenFull;
	int drawPotential;
	
	int x, y;

	double percentage, potentialPercentage;

public:

	ProgressBar(int x, int y, int width, int height, int borderSize, int drawWhenFull);

	void setSize(int newWidth, int newHeight);
	void setBorderSize(int newBorderSize);

	void setProgressColor(Color newProgressColor);
	void setWaitColor(Color newWaitColor);
	void setBorderColor(Color newBorderColor);
	void setPotentialColor(Color newPotentialColor);

	void setDrawPotential(int newDrawPotential);

	void setPosition(int newX, int newY);

	void update(double currentPercetnage);
	void setPotentialPercentage(double newPotentialPercentage);
	void draw(RenderWindow* window);

};