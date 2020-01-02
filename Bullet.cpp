#include "Bullet.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}


void Bullet::create(double _positionX, double _positionY, double _angle, double _speed, int _damage, bool _isPlayerTarget)
{
	/*
	* function of initialization
	*
	* @param positionX, positionY - position
	*        angle - angle of vector of moving
	*        speed - speed of moving
	*        damage - damage of bullet
	*        isPlayerTarget - true if bullet created by players` weapon
	*/

	positionX = _positionX;
	positionY = _positionY;

	angle = _angle;
	speed = _speed;

	damage = _damage;
	isPlayerTarget = _isPlayerTarget;

	timerOfLife = 0;

	return;
}

void Bullet::move(double timer)
{
	/*
	* function of moving
	*
	* @param timer - how much time has been passed
	*/

	// increase timer of lofe
	timerOfLife += timer;

	// move
	positionX += timer * speed * cos(angle);
	positionY += timer * speed * sin(angle);

	return;
}

bool Bullet::readyToDelete()
{
	/*
	* function of sheking time for delete
	*
	* @return true - if bullet live too long
	*         false - if not
	*/

	return timerOfLife > TIME_OF_BULLET_LIFE;
}

pair < double, double > Bullet::getPosition()
{
	/*
	* function of getting position of bullet
	*
	* @return current bullet position
	*/

	return{ positionX, positionY };
}