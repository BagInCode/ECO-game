#include "Player.h"

bool Player::create()
{
	/*
	* function of initialization player
	*
	* @return true - if initialization completed
	*         false - if initialization failed
	*/

	// if did not load file
	if (!PlayerTexture.loadFromFile("Textures\\Player.png"))
	{
		// initialization failed
		return 0;
	}

	// set texture image to player sprite
	PlayerSprite.setTexture(PlayerTexture);

	// set player sprite size 
	spriteHigh = PLAYER_SPRITE_AK_HIGH;
	spriteLength = PLAYER_SPRITE_AK_LENGTH;

	// set texture rectangle to the player sprite
	PlayerSprite.setTextureRect(IntRect(0, 0, spriteLength, spriteHigh));

	// set origin of sprite to center
	PlayerSprite.setOrigin(spriteLength / 2., spriteHigh / 2.);

	// set player position
	playerPositionX = FIELD_SIZE / 2 * SQUARE_SIZE_PIXIL;
	playerPositionY = FIELD_SIZE / 2 * SQUARE_SIZE_PIXIL;

	// initialization complited
	return 1;
}

void Player::setSprite(int spritePositionX, int spritePositionY, int newSpriteLength, int newSpriteHigh)
{
	/*
	* function of resetting player sprite
	*
	* @param spritePositionX, spritePositionY - position of top left pixil of image in texture file
	*        newSpriteLength, newSpriteHigh - sprite image size
	*/

	// setting new sprite size
	spriteHigh = newSpriteHigh;
	spriteLength = newSpriteLength;

	// setting new sprite image
	PlayerSprite.setTextureRect(IntRect(spritePositionX, spritePositionY, spriteLength, spriteHigh));

	// set origin of sprite to center
	PlayerSprite.setOrigin(spriteLength / 2., spriteHigh / 2.);

	return;
}

void Player::draw(RenderWindow& window)
{
	/*
	* function of drawing player sprite in game window
	*
	* @param window - game window
	*/

	// get player position inside game window
	double playerPositionInWindowX = getPositionInWindow().first;
	double playerPositionInWindowY = getPositionInWindow().second;

	// get angle and position of rotation
	rotate(window, playerPositionInWindowX, playerPositionInWindowY);

	// rotate sprite
	PlayerSprite.setRotation(angle * 180 / acos(-1));

	// set sprite position
	PlayerSprite.setPosition(playerPositionInWindowX, playerPositionInWindowY);

	// drawing sprite
	window.draw(PlayerSprite);

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
	if (playerPositionX < spriteLength / 2. || playerPositionX > FIELD_SIZE* SQUARE_SIZE_PIXIL - spriteLength / 2.)
	{
		playerPositionX = max(min(playerPositionX, FIELD_SIZE * SQUARE_SIZE_PIXIL - spriteLength / 2.), spriteLength / 2.);
	}

	if (playerPositionY < spriteHigh / 2. || playerPositionY > FIELD_SIZE* SQUARE_SIZE_PIXIL - spriteHigh / 2.)
	{
		playerPositionY = max(min(playerPositionY, FIELD_SIZE * SQUARE_SIZE_PIXIL - spriteHigh / 2.), spriteHigh / 2.);
	}

	return;
}

void Player::setMoovingVector(int newVectorX, int newVectorY)
{
	/*
	* function of updating speed vector
	*
	* @param newVectorX, newVectorY - new speed vector
	*/

	// if new vector in range {-1, 0, 1} - change it
	if (newVectorX < 2 && newVectorX > -2)
	{
		vectorX = newVectorX;
	}

	if (newVectorY < 2 && newVectorY > -2)
	{
		vectorY = newVectorY;
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

	return { playerPositionX, playerPositionY };
}

pair < double, double > Player::getPositionInWindow()
{
	/*
	* function of getting player position inside the window
	*
	* @return player position inside the window
	*/

	// set position in centre of window
	double resultPositionX = (WINDOW_LENGTH - spriteLength) / 2;
	double resultPositionY = (WINDOW_HIGH - spriteHigh) / 2;

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
	return { resultPositionX, resultPositionY };
}

void Player::rotate(RenderWindow & window, double positionX, double positionY)
{
	/*
	* function of changing angle to order sprite by mouse
	*
	* @param positionX, positionY - position of center of sprite image
	*        window - game window
	*/

	// get mouse position inside the window
	Vector2i mousePosition = Mouse::getPosition(window);

	// if mouse inside the widow change - angle of rotation
	if (mousePosition.x >= 0 && mousePosition.x <= WINDOW_LENGTH && mousePosition.y >= 0 && mousePosition.y <= WINDOW_HIGH)
	{
		// get coordinats of vector (center of sprite -> mouse)
		double deltX = mousePosition.x - positionX;
		double deltY = mousePosition.y - positionY;

		// get angle of this vector with vector (0, 1)
		angle = atan2(deltY, deltX);
	}

	return;
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