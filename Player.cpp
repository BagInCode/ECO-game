#include "Player.h"

Player::Player()
{
}


Player::~Player()
{
}



pair < double, double > Player::getPosition()
{
	/*
	* function of getting player global (on map) position
	*
	* @return player global position
	*/

	return { positionX, positionY };
}


pair < double, double > Player::getPositionInWindow()
{
	/*
	* function of calculating and getting player local (in window) position without rotation
	*
	* @return player local position without rotation
	*/

	// default player stay at centre of window
	double positionInWindowX = (WINDOW_LENGTH - PLAYER_SPRITE_LENGTH) / 2;
	double positionInWindowY = (WINDOW_HIGH - PLAYER_SPRITE_HIGH) / 2;

	// if payer closer to right border of map 
	// then centre of window to right border of window
	// update position 
	if (positionInWindowX > positionX)
	{
		positionInWindowX = positionX;
	}

	// if payer closer to left border of map 
	// then centre of window to left border of window
	// update position 
	if (WINDOW_LENGTH - positionInWindowX > FIELD_LENGTH_PIXIL - positionX)
	{
		positionInWindowX = WINDOW_LENGTH - (FIELD_LENGTH_PIXIL - positionX);
	}

	// if payer closer to lower border of map 
	// then centre of window to lower border of window
	// update position 
	if (positionInWindowY > positionY)
	{
		positionInWindowY = positionY;
	}

	// if payer closer to upper border of map 
	// then centre of window to upper border of window
	// update position 
	if (WINDOW_HIGH - positionInWindowY > FIELD_HIGH_PIXIL - positionY)
	{
		positionInWindowY = WINDOW_HIGH - (FIELD_HIGH_PIXIL - positionY);
	}

	// return position
	return { positionInWindowX, positionInWindowY };
}

double Player::getAngle()
{
	/*
	*  function of getting player angle
	*
	* @return angle
	*/

	return angle;
}

int Player::getHealthPoints()
{
	/*
	* function of getting player health points
	*
	* @return player health points
	*/

	return healthPoints;
}

int Player::getArmorPoints()
{
	/*
	* function of getting player armor points
	*
	* @return player armor points
	*/

	return armorPoints;
}

void Player::setPosition(double newPositionX, double newPositionY)
{
	/*
	* function of setting player global (on map) position
	*
	* @param newPlayerPositionX, newPlayerPositionY - new global position
	*/

	positionX = newPositionX;
	positionY = newPositionY;

	return;
}

void Player::setArmorPoints(int newArmorPoints)
{
	/*
	* function of setting player armor posints
	*
	* @param newArmorPoints - new armor points
	*/

	armorPoints = newArmorPoints;

	return;
}

void Player::setHealthPoints(int newHealthPoints)
{
	/*
	* function of setting player health points
	*
	* @param newHealthPoints - new health points
	*/

	healthPoints = newHealthPoints;

	return;
}

void Player::setKeyUpPressed(bool newValue)
{
	/*
	* function of setting key up pressed value
	*
	* @param newValue - true if key pressed
	*                   false if key released
	*/

	keyUpMovePressed = newValue;

	return;
}

void Player::setKeyDownPressed(bool newValue)
{
	/*
	* function of setting key down pressed
	*
	* @param newValue - true if key pressed
	*                   false if key released
	*/

	keyDownMovePressed = newValue;

	return;
}

void Player::setKeyLeftPressed(bool newValue)
{
	/*
	* function of setting key left pressed
	*
	* @param newValue - true if key pressed
	*                   false if key released
	*/

	keyLeftMovePressed = newValue;
}

void Player::setKeyRightPressed(bool newValue)
{
	/*
	* function of setting
	*
	* @param newValue - true if key pressed
	*                   false if key released
	*/

	keyRightMovePressed = newValue;
}

void Player::move(double timer)
{
	/*
	* function of updating player position
	*
	* @param timer - how much time has been passed
	*/

	// update position
	positionX += ((keyRightMovePressed * timer) -  (keyLeftMovePressed * timer)) * PLAYER_SPEED;
	positionY += ((keyDownMovePressed * timer) - (keyUpMovePressed * timer)) * PLAYER_SPEED;

	// if position is out of map - return it inside
	if (positionX < 0)
	{
		positionX = 0;
	}
	if (positionX > FIELD_LENGTH_PIXIL - PLAYER_SPRITE_LENGTH)
	{
		positionX = FIELD_LENGTH_PIXIL - PLAYER_SPRITE_LENGTH;
	}

	if (positionY < 0)
	{
		positionY = 0;
	}
	if (positionY > FIELD_HIGH_PIXIL - PLAYER_SPRITE_HIGH)
	{
		positionY = FIELD_HIGH_PIXIL - PLAYER_SPRITE_HIGH;
	}

	return;
}

void Player::draw(RenderWindow & window)
{
	/*
	* function of drawing sprite in window
	*
	* @param window - window of game
	*/

	// get position in window
	pair < double, double > positionInWindow = getPositionInWindow();

	// find centre of rotation
	double centreX = positionInWindow.first + PLAYER_SPRITE_LENGTH / 2;
	double centreY = positionInWindow.second + PLAYER_SPRITE_HIGH / 2;
		
	// get mous position inside window
	Vector2i MousePosition = Mouse::getPosition(window);

	// if mouse is inside window
	if (MousePosition.x > 0 && MousePosition.x < WINDOW_LENGTH &&
		MousePosition.y > 0 && MousePosition.y < WINDOW_HIGH)
	{
		// calculate angle of rotation
		angle = atan2(MousePosition.y - centreY, MousePosition.x - centreX);
	}

	// calculate radius of rotation
	double radius = sqrt((PLAYER_SPRITE_LENGTH / 2)*(PLAYER_SPRITE_LENGTH / 2) + (PLAYER_SPRITE_HIGH / 2)*(PLAYER_SPRITE_HIGH / 2));

	// calculate final position in window (with rotation)
	positionInWindow.first = centreX + cos(angle + 5*PI/4)*radius;
	positionInWindow.second = centreY + sin(angle + 5*PI/4)*radius;

	// set roation of player sprite
	PlayerSpirite.setRotation(angle*180/PI);

	// set position of player sprite
	PlayerSpirite.setPosition(positionInWindow.first, positionInWindow.second);

	// draw player sprite
	window.draw(PlayerSpirite);
	
	return;
}

bool Player::loadSprite()
{
	/*
	* function of loading player textures and sprite
	*
	* @return true - if loading completed
	*         false - if loading failed
	*/

	// if texture dowasn`t load 
	if (!PlayerTexture.loadFromFile("Textures\\Player.png"))
	{
		// loading failed -> return false
		return 0;
	}

	// set texture and rectangle inside texture
	PlayerSpirite.setTexture(PlayerTexture);
	PlayerSpirite.setTextureRect(IntRect(PLAYER_SPRITE_POSITION_X, PLAYER_SPRITE_POSITION_Y, PLAYER_SPRITE_LENGTH, PLAYER_SPRITE_HIGH));

	// loading completed
	return 1;
}

bool Player::create(double newPositionX, double newPositionY, int healthPoints, int armorPoints)
{
	/*
	* function of initialization player object
	*
	* @param newPositionX, newPositionY - player global (on map) position
	*        healthPoints - health points
	*        armorPoints - armor points
	*
	* @return true - if initialization completed
	*         false - if initialization failed
	*/

	// if sprite doesn`t load
	if (!loadSprite())
	{
		// initialization failed -> return false
		return 0;
	}

	// set values
	setPosition(newPositionX, newPositionY);
	setHealthPoints(healthPoints);
	setArmorPoints(armorPoints);

	// initialization completed
	return 1;
}