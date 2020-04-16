#include "ToggleBox.h"

ToggleBox::ToggleBox(float x, float y, float width, float height, float pointerHeight, float pointerWidth, Texture pointerTexture, Font& font) :
positionX(x), positionY(y), height(height), width(width), pointerHeight(pointerHeight), pointerWidth(pointerWidth), pointerTexture(pointerTexture)
{
	caseIndex = 0;

	mainShape.setPosition(Vector2f(x, y));
	mainShape.setSize(Vector2f(width, height));
	mainShape.setFillColor(Color::White);

	Sprite leftPointerSprite, rightPointerSprite;
	leftPointerSprite.setTexture(this->pointerTexture);
	leftPointerSprite.setTextureRect(IntRect(0, 0, pointerTexture.getSize().x / 2.0, pointerTexture.getSize().y));
	rightPointerSprite.setTexture(this->pointerTexture);
	rightPointerSprite.setTextureRect(IntRect(pointerTexture.getSize().x / 2, 0, pointerTexture.getSize().x / 2.0, pointerTexture.getSize().y));

	leftPointer = new Button(x, y + height / 2.0 - pointerHeight / 2.0, pointerHeight, pointerWidth, font, "", Color(255, 255, 255),
		Color(255, 255, 255), Color(255, 255, 255));
	leftPointer->setBackgroundImage(leftPointerSprite);
	rightPointer = new Button(x + width - pointerWidth, y + height / 2.0 - pointerHeight / 2.0, pointerHeight, pointerWidth, font, "",
		Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255));
	rightPointer->setBackgroundImage(rightPointerSprite);

	text.setFont(font);
	text.setCharacterSize(60);
	text.setFillColor(Color::Red);
	text.setOutlineThickness(2);
	text.setOutlineColor(Color::Black);
}

ToggleBox::~ToggleBox()
{
	delete leftPointer;
	delete rightPointer;
}

void ToggleBox::addCase(string txt)
{
	cases.push_back(txt);

	text.setString(cases[caseIndex]);
	text.setPosition(positionX + width / 2.0 - text.getLocalBounds().width / 2.0, positionY + height / 2.0 - text.getLocalBounds().height / 2.0 - 15.0);
}

void ToggleBox::setCaseIndex(int index)
{
	caseIndex = index;

	text.setString(cases[caseIndex]);
	text.setPosition(positionX + width / 2.0 - text.getLocalBounds().width / 2.0, positionY + height / 2.0 - text.getLocalBounds().height / 2.0 - 15.0);
}

int ToggleBox::getCaseIndex()
{
	return caseIndex;
}

void ToggleBox::update(RenderWindow &window)
{
	Vector2f mousePosition(Mouse::getPosition(window));
	mousePosition.x *= float(WINDOW_LENGTH) / float(window.getSize().x);
	mousePosition.y *= float(WINDOW_HIGH) / float(window.getSize().y);

	leftPointer->updateState(mousePosition);
	if (leftPointer->isPressed())
	{
		caseIndex = max(caseIndex - 1, 0);
	}

	rightPointer->updateState(mousePosition);
	if (rightPointer->isPressed())
	{
		caseIndex = min(caseIndex + 1, int(cases.size()) - 1);
	}

	text.setString(cases[caseIndex]);
	text.setPosition(positionX + width / 2.0 - text.getLocalBounds().width / 2.0, positionY + height / 2.0 - text.getLocalBounds().height / 2.0 - 15.0);
}

void ToggleBox::draw(RenderWindow &window)
{
	window.draw(mainShape);
	leftPointer->draw(window);
	rightPointer->draw(window);
	window.draw(text);
}