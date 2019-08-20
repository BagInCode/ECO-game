#include "Bullet.h"



Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

void Bullet:: setAngle(double newAngle)
{
	/*
	* function of setting angle of moving
	*
	* @param newAngle - new angle
	*/

	angle = newAngle;

	return;
}

void Bullet::setPosition(double newPositionX, double newPositionY)
{
	/*
	* function of setting global (on map) position for bullet sprite
	*
	* @param newPositionX, newPositionY - new position
	*/

	positionX = newPositionX;
	positionY = newPositionY;

	return;
}

void Bullet::setTerget(double newIsPlayerTarget)
{
	/*
	* function of setting target
	*
	* @param newIsPlayerTarget - true if target is player
	*                            false if target is enemy
	*/

	isPlayerTarget = newIsPlayerTarget;

	return;
}

void Bullet::setDamage(int newDamage)
{
	/*
	* function of setting bullet damage
	*
	* @param newDamage - new damage
	*/

	damage = newDamage;

	return;
}

double Bullet::getAngle()
{
	/*
	* function of getting angle of moving
	*
	* @return angle of bullets` moving
	*/

	return angle;
}

double Bullet::getTimeOfLife()
{
	/*
	* function of getting how long has bullet lived
	*
	* @return how long has bullet lived
	*/

	return timeOfLife;
}

pair < double, double > Bullet::getPosition()
{
	/*
	* function of getting bullet global (on map) position
	*
	* @return global bullet position
	*/

	return { positionX, positionY };
}

bool Bullet::getTarget()
{
	/*
	* function of getting target
	*
	* @return true - if target is player
	*         false - if target is enemy
	*/

	return isPlayerTarget;
}

int Bullet::getDamage()
{
	/*
	* function of getting bullet damage
	*
	* @return bullet damage
	*/

	return damage;
}

bool Bullet::loadSprite()
{
	/*
	* function of loading bullet sprite and texture
	*
	* @return true - if loading completed
	*         false - if loading failed
	*/

	// if texture doesn`t load
	if (!bulletTexture.loadFromFile("Textures\\BulletTexture.png"))
	{
		// loading failed -> return false
		return 0;
	}

	//load texture to sprite, set picture rectangle and picture color
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setTextureRect(IntRect(BULLET_SPRITE_POSITION_X, BULLET_SPRITE_POSITION_Y, BULLET_SPRITE_LENGTH, BULLET_SPRITE_HIGH));
	bulletSprite.setColor(Color::Red);

	// loading completed -> return true
	return 1;
}

bool Bullet::create(double _angle, double _positionX, double _positionY, bool _isPlayerTarget, int _damage)
{
	/*
	* function of creating bullet object
	*
	* @param _angle - angle of moving
	*        _positionX, _positionY - global (on map) bullet position
	*        _isPlayerTarget - true if target is player
	*                          false if target is enemy
	*        _damage - bullet damage
	*
	* @return true - if creation completed
	*         false - if creation failed
	*/

	// if sprite doesn`t loaded
	if (!loadSprite())
	{
		// creation failed -> return false
		return 0;
	}

	// set values
	angle = _angle;
	positionX = _positionX;
	positionY = _positionY;
	isPlayerTarget = _isPlayerTarget;
	damage = _damage;
	timeOfLife = 0;

	// creation completed
	return 1;
}

void Bullet::move(double timer)
{
	/*
	* function of moving bullet and increasing time of life
	*
	* @param timer - how much time has been passed
	*/

	// update position
	positionX += timer * BULLET_SPEED * cos(angle);
	positionY += timer * BULLET_SPEED * sin(angle);

	// increase time of life
	timeOfLife += timer;

	return;
}

void Bullet::draw(RenderWindow & window, double _positionX, double _positionY)
{
	/*
	* function of drawing sprite in some position inside game window
	*
	* @param window - window of game
	*        _positionX, _positionY - position inside game window
	*/

	// set position for sprite
	bulletSprite.setPosition(_positionX, _positionY);
	
	// draw sprite in window
	window.draw(bulletSprite);

	return;
}