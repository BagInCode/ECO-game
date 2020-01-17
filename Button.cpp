#include "Button.h"

Button::Button(float x, float y, float width, float height, Font font, string text,
	Color idleColor, Color hoverColor, Color activeColor) :
	idleColor(idleColor), hoverColor(hoverColor), activeColor(activeColor)
{
	buttonState = { BUTTON_STATE::BUTTON_IDLE, BUTTON_STATE::BUTTON_IDLE };

	shape.setPosition(Vector2f(x, y));
	shape.setSize(Vector2f(width, height));

	this->font = font;
	this->text.setFont(this->font);
	this->text.setString(text);
	this->text.setFillColor(Color::White);
	this->text.setCharacterSize(12);
	this->text.setPosition(
		shape.getPosition().x + shape.getGlobalBounds().width / 2.0 - this->text.getGlobalBounds().width / 2.0,
		shape.getPosition().y + shape.getGlobalBounds().height / 2.0 - this->text.getGlobalBounds().height / 2.0
		);
}

Button::~Button()
{

}

void Button::setTextSize(int textSize)
{
	text.setCharacterSize(textSize);
	text.setPosition(
		shape.getPosition().x + shape.getGlobalBounds().width / 2.0 - text.getGlobalBounds().width / 2.0,
		shape.getPosition().y + shape.getGlobalBounds().height / 2.0 - text.getGlobalBounds().height / 2.0
		);
}

bool Button::isPressed()
{
	if (buttonState.second == BUTTON_STATE::BUTTON_ACTIVE && buttonState.first == BUTTON_STATE::BUTTON_HOVER)
	{
		return true;
	}

	return false;
}

void Button::updateState(Vector2f mousePosition)
{
	buttonState.second = buttonState.first;

	buttonState.first = BUTTON_STATE::BUTTON_IDLE;

	if (shape.getGlobalBounds().contains(mousePosition))
	{
		buttonState.first = BUTTON_STATE::BUTTON_HOVER;

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			buttonState.first = BUTTON_STATE::BUTTON_ACTIVE;
		}
	}

	switch (buttonState.first)
	{
	case BUTTON_STATE::BUTTON_IDLE:
		shape.setFillColor(idleColor);
		break;
	case BUTTON_STATE::BUTTON_HOVER:
		shape.setFillColor(hoverColor);
		break;
	case BUTTON_STATE::BUTTON_ACTIVE:
		shape.setFillColor(activeColor);
		break;
	default:
		_ASSERT("ButtonError#1(wrong state)" == "");
	}
}

void Button::draw(RenderWindow& window)
{
	window.draw(shape);
	window.draw(text);
}