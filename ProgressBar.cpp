#include "ProgressBar.h"

ProgressBar::ProgressBar(int x, int y, int width = 100, int height = 20, int borderSize = 2, int drawWhenFull = 0) : x(x),
y(y), width(width), height(height), borderSize(borderSize), drawWhenFull(drawWhenFull)
{
	progressColor = Color::Green;
	waitColor = Color::Red;
	borderColor = Color::Black;
	potentialColor = Color::Yellow;

	borderRectangle.setPosition(Vector2f(float(x), float(y)));
	borderRectangle.setSize(Vector2f(float(width + 2 * borderSize), float(height + 2 * borderSize)));
	borderRectangle.setFillColor(borderColor);
	waitRectangle.setPosition(Vector2f(float(x + borderSize), float(y + borderSize)));
	waitRectangle.setSize(Vector2f(float(width), float(height)));
	waitRectangle.setFillColor(waitColor);
	progressRectangle.setPosition(Vector2f(float(x + borderSize), float(y + borderSize)));
	progressRectangle.setSize(Vector2f(float(width), float(height)));
	progressRectangle.setFillColor(progressColor);
	potentialRectangle.setPosition(Vector2f(float(x + borderSize), float(y + borderSize)));
	potentialRectangle.setSize(Vector2f(float(width), float(height)));
	potentialRectangle.setFillColor(potentialColor);

	percentage = 1.0;
	potentialPercentage = 0.0;
}

void ProgressBar::setSize(int newWidth, int newHeight)
{
	width = newWidth;
	height = newHeight;

	borderRectangle.setPosition(Vector2f(float(x), float(y)));
	borderRectangle.setSize(Vector2f(float(width + 2 * borderSize), float(height + 2 * borderSize)));
	waitRectangle.setPosition(Vector2f(float(x + borderSize), float(y + borderSize)));
	waitRectangle.setSize(Vector2f(float(width), float(height)));
	progressRectangle.setPosition(Vector2f(float(x + borderSize), float(y + borderSize)));
	progressRectangle.setSize(Vector2f(float(width), float(height)));
	potentialRectangle.setPosition(Vector2f(float(x + borderSize), float(y + borderSize)));
	potentialRectangle.setSize(Vector2f(float(width), float(height)));
}

void ProgressBar::setBorderSize(int newBorderSize)
{
	borderSize = newBorderSize;

	borderRectangle.setPosition(Vector2f(float(x), float(y)));
	borderRectangle.setSize(Vector2f(float(width + 2 * borderSize), float(height + 2 * borderSize)));
	waitRectangle.setPosition(Vector2f(float(x + borderSize), float(y + borderSize)));
	waitRectangle.setSize(Vector2f(float(width), float(height)));
	progressRectangle.setPosition(Vector2f(float(x + borderSize), float(y + borderSize)));
	progressRectangle.setSize(Vector2f(float(width), float(height)));
	potentialRectangle.setPosition(Vector2f(float(x + borderSize), float(y + borderSize)));
	potentialRectangle.setSize(Vector2f(float(width), float(height)));
}

void ProgressBar::setProgressColor(Color newProgressColor)
{
	progressColor = newProgressColor;
	progressRectangle.setFillColor(progressColor);
}

void ProgressBar::setWaitColor(Color newWaiColor)
{
	waitColor = newWaiColor;
	waitRectangle.setFillColor(waitColor);
}

void ProgressBar::setBorderColor(Color newBorderColor)
{
	borderColor = newBorderColor;
	borderRectangle.setFillColor(borderColor);
}

void ProgressBar::setPotentialColor(Color newPotentialColor)
{
	potentialColor = newPotentialColor;
	potentialRectangle.setFillColor(borderColor);
}

void ProgressBar::setDrawPotential(int newDrawPotential)
{
	drawPotential = newDrawPotential;
}

void ProgressBar::setPosition(int newX, int newY)
{
	x = newX;
	y = newY;

	borderRectangle.setPosition(Vector2f(float(x), float(y)));
	waitRectangle.setPosition(Vector2f(float(x + borderSize), float(y + borderSize)));
	progressRectangle.setPosition(Vector2f(float(x + borderSize), float(y + borderSize)));
	potentialRectangle.setPosition(Vector2f(float(x + borderSize), float(y + borderSize)));
}

void ProgressBar::update(double currentPercentage)
{
	percentage = currentPercentage;
	
	progressRectangle.setSize(Vector2f(float(width*percentage), float(height)));

	if (drawPotential == 1)
	{
		potentialRectangle.setSize(Vector2f(float(min(double(width), width*(percentage + potentialPercentage))), float(height)));
	}
}

void ProgressBar::setPotentialPercentage(double newPotentialPercentage)
{
	potentialPercentage = newPotentialPercentage;

	potentialRectangle.setSize(Vector2f(float(min(double(width), width*(percentage + potentialPercentage))), float(height)));
}

void ProgressBar::draw(RenderWindow* window)
{
	if (drawWhenFull == 0 && percentage >= 0.99999)
	{
		return;
	}

	window->draw(borderRectangle);
	window->draw(waitRectangle);
	if (drawPotential == 1)
	{
		window->draw(potentialRectangle);
	}
	window->draw(progressRectangle);
}