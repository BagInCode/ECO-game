#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

Weapon* Enemy::getWeaponPointer()
{
	/*
	* function of getting pointer to weapon
	*
	* @return pointer to weapon of this enemy
	*/

	return &myWeapon;
}

void Enemy::move(double timer, double speed)
{
	/*
	* function of updating position
	*
	* @param timer - how much time has been passed
	*        speed - speed of moving
	*/

	// overwrite previous position
	previousPosition = { positionX, positionY };

	// update position
	positionX += speed * timer * cos(angleMoving);
	positionY += speed * timer * sin(angleMoving);

	// if enemy position is out of field -> get it back
	positionX = max(min(positionX, FIELD_SIZE * SQUARE_SIZE_PIXIL - spriteLength / 2.), spriteLength / 2.);
	positionY = max(min(positionY, FIELD_SIZE * SQUARE_SIZE_PIXIL - spriteHigh / 2.), spriteHigh / 2.);

	return;
}

void Enemy::calculateAngleWatching(Player& player)
{
	/*
	* function of calculating angle betwen vector (0, 1) and vector (enemy position -> player position)
	*
	* @param player - player
	*/
	
	// get vector (enemy -> player)
	double vectorX = player.getPosition().first - positionX;
	double vectorY = player.getPosition().second - positionY;

	// get angle
	angleWathcing = atan2(vectorY, vectorX);

	return;
}

double Enemy::getAngleWatching()
{
	/*
	* function of getting angle of watching
	*
	* @return angleWatching - angle of watching
	*/

	return angleWathcing;
}

void Enemy::setAngleMoving(double _angleMoving)
{
	/*
	* function of setting angle of moving
	*
	* @param _angleMoving - new angle of moving
	*/

	angleMoving = _angleMoving;

	return;
}

pair < double, double > Enemy::getPosition()
{
	/*
	* function of getting position
	*
	* @return position on map
	*/

	return { positionX, positionY };
}

void Enemy::doAction(double timer)
{
	/*
	* function of doing action
	*
	* @param timer - how much time has been passed
	*/

	// increase weapon timer
	myWeapon.increaseTimer(timer);

	return;
}

pair < double, double > Enemy::getSize()
{
	/*
	* function of getting sprite size
	*
	* @retrun sprite size
	*/

	return { spriteLength, spriteHigh };
}

void Enemy::setPosition(double newX, double newY)
{
	/*
	* function of setting position
	*
	* @param newX, newY - new position
	*/

	positionX = newX;
	positionY = newY;

	return;
}

void Enemy::create(double _positionX, double _positionY, Weapon weapon)
{
	/*
	* function of intialization enemy object
	*
	* @param positionX, positionY - start position
	*        weapon - weapon
	*/

	positionX = _positionX;
	positionY = _positionY;

	previousPosition = { positionX, positionY };

	spriteLength = ENEMY_SPRITE_LENGTH;
	spriteHigh = ENEMY_SPRITE_HIGH;

	healthPoints = 10;

	myWeapon = weapon;
}

void Enemy::setAngleWatching(double angle)
{
	/*
	* function of setting angle of watching
	*
	* @param angle - new angle
	*/

	angleWathcing = angle;

	return;
}

void Enemy::getDamage(int damage)
{
	/*
	* function of decreasing enemys hp
	*
	* @param damage - damage
	*/

	healthPoints -= damage;
}

bool Enemy::isDead()
{
	/*
	* function of chekcing enemy hp 
	*/

	return healthPoints < 1;
}

pair < double, double > Enemy::getPreviousPosition()
{
	/*
	* function of getting previous position
	*
	* @return previous position 
	*/
	return previousPosition;
}