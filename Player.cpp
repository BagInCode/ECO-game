#include "Player.h"

void Player::create()
{
	/*
	* function of initialization player
	*/

	isDamaged = 0;

	// set position
	playerPositionX = FIELD_SIZE * SQUARE_SIZE_PIXIL / 2.;
	playerPositionY = FIELD_SIZE * SQUARE_SIZE_PIXIL / 2.;

	// set player sprite size
	spriteLength = PLAYER_SPRITE_AK_LENGTH;
	spriteHigh = PLAYER_SPRITE_AK_HIGH;

	// set health points
	healthPoints = 100;
	armor = 100;

	engramPoints = 0;

	return;
}

void Player::move(double timer)
{
	/*
	* function of updating player position
	*
	* @param timer - count elapsed time in ms
	*/

	// calculating delt by ordinate and abscis
	double delt = sqrt(abs(vectorX) * abs(vectorX) + abs(vectorY) * abs(vectorY));

	// if no moving, we may get dividing by zero, solve this problem
	if (vectorX == 0 && vectorY == 0)
	{
		delt = 1;
	}

	// updating player position
	playerPositionX = playerPositionX + vectorX * PLAYER_SPEED * timer / delt;
	playerPositionY = playerPositionY + vectorY * PLAYER_SPEED * timer / delt;

	// if player position is out of field - get it inside
	playerPositionX = max(min(playerPositionX, FIELD_SIZE * SQUARE_SIZE_PIXIL - spriteLength / 2.), spriteLength / 2.);
	playerPositionY = max(min(playerPositionY, FIELD_SIZE * SQUARE_SIZE_PIXIL - spriteHigh / 2.), spriteHigh / 2.);


	return;
}

void Player::setMovingVector(int newVectorX, int newVectorY)
{
	/*
	* function of setting moving vector
	*
	* @param newVectorX, newVectorY - new mooving vector
	*/

	// if new vector in range {-1, 0, 1} - change it
	if (newVectorX > -2 && newVectorX < 2)
	{
		vectorX = newVectorX;
	}

	if (newVectorY > -2 && newVectorY < 2)
	{
		vectorY = newVectorY;
	}
}

void Player::updateMovingVector(int deltX, int deltY)
{
	/*
	* function of updating speed vector
	*
	* @param newVectorX, newVectorY - new speed vector
	*/

	// if new vector in range {-1, 0, 1} - change it
	if (deltX > -2 && deltX < 2)
	{
		vectorX += deltX;
	}

	if (deltY > -2 && deltY < 2)
	{
		vectorY += deltY;
	}

	return;
}

pair < double, double > Player::getPosition()
{
	/*
	* function of getting player position
	*
	* @return player position
	*/

	return{ playerPositionX, playerPositionY };
}

pair < double, double > Player::getPositionInWindow()
{
	/*
	* function of getting player position inside the window
	*
	* @return player position inside the window
	*/

	// set position in centre of window
	double resultPositionX = WINDOW_LENGTH / 2;
	double resultPositionY = WINDOW_HIGH / 2;

	// if player is to close to left border - move position
	if (playerPositionX < resultPositionX)
	{
		resultPositionX = playerPositionX;
	}

	// if player is to close to up border - move position
	if (playerPositionY < resultPositionY)
	{
		resultPositionY = playerPositionY;
	}

	// if player is to close to right border - move position
	if (WINDOW_LENGTH - resultPositionX > FIELD_SIZE * SQUARE_SIZE_PIXIL - playerPositionX)
	{
		resultPositionX = WINDOW_LENGTH - FIELD_SIZE * SQUARE_SIZE_PIXIL + playerPositionX;
	}

	// if player is to close to down border - move position
	if (WINDOW_HIGH - resultPositionY > FIELD_SIZE * SQUARE_SIZE_PIXIL - playerPositionY)
	{
		resultPositionY = WINDOW_HIGH - FIELD_SIZE * SQUARE_SIZE_PIXIL + playerPositionY;
	}

	// return result
	return{ resultPositionX, resultPositionY };
}

pair < double, double > Player::getSize()
{
	/*
	* function of getting player sprite size
	*
	* @return size of player sprite
	*/

	return{ spriteLength, spriteHigh };
}

double Player::rotate(RenderWindow* window)
{
	/*
	* function of changing angle to order sprite by mouse
	*
	* @param window - game window
	* @return new angle
	*/

	// get position of center sprite in window
	double positionX = getPositionInWindow().first;
	double positionY = getPositionInWindow().second;

	// get mouse position inside the window
	Vector2i mousePosition = Mouse::getPosition(*window);


	mousePosition.x = int(mousePosition.x / double(window->getSize().x) * WINDOW_LENGTH);
	mousePosition.y = int(mousePosition.y / double(window->getSize().y) * WINDOW_HIGH);


	// if mouse inside the widow change - angle of rotation
	if (mousePosition.x >= 0 && mousePosition.x <= WINDOW_LENGTH && mousePosition.y >= 0 && mousePosition.y <= WINDOW_HIGH)
	{
		// get coordinats of vector (center of sprite -> mouse)
		double deltX = mousePosition.x - positionX;
		double deltY = mousePosition.y - positionY;

		// get angle of this vector with vector (0, 1)
		angle = atan2(deltY, deltX);
	}

	return angle;
}

double Player::getAngle()
{
	/*
	* function of getting player angle
	*
	* @return player angle
	*/

	return angle;
}

void Player::setPosition(double newX, double newY)
{
	/*
	* function of setting player position
	*
	* @param newX, newY - new position
	*/

	playerPositionX = newX;
	playerPositionY = newY;

	return;
}

int Player::getHealthPoints()
{
	/*
	* function of getting player health points
	*
	* @return health points
	*/

	return healthPoints;
}

void Player::addHealthPoints(int value)
{
	healthPoints = min(healthPoints + value, 100);
}

int Player::getEngramPoints()
{
	return engramPoints;
}

void Player::addEngramPoints(int value)
{
	engramPoints += value;
}

void Player::decrEngramPoints(int value)
{
	engramPoints -= value;
}

void Player::getDamage(int damage)
{
	/*
	* function of decreasing player HP
	*
	* @param damage - damage
	*/

	healthPoints -= damage;

	return;
}

void Player::setSize(double length, double high)
{
	/*
	* function of setting player sprite size
	*
	* @param length - new length
	*        high - new high
	*/

	spriteLength = int(length);
	spriteHigh = int(high);
}