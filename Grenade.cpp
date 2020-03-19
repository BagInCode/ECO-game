#include "Grenade.h"


Grenade::Grenade()
{
}


Grenade::~Grenade()
{
}

void Grenade::create(Player& player, RenderWindow* window)
{
	/*
	* function of creating grenade
	*
	* @param player - player object
	*        window - game window
	*/

	// get angle of moving
	angle = player.getAngle();

	// get position
	positionX = player.getPosition().first;
	positionY = player.getPosition().second;

	// calc speed
	speed = calculteSpeed(player, window);

	// set other values
	timer = 0;
	numberPictureToDraw = 0;
	detonate = 0;

	return;
}

double Grenade::calculteSpeed(Player& player, RenderWindow* window)
{
	/*
	* function of calcing speed of mooving
	*
	* @param player - player object
	*        window - game window
	*
	* @return speed of moving
	*/

	// get position of mouse in window
	Vector2i mousePosition = Mouse::getPosition(*window);
	mousePosition.x = int(mousePosition.x * double(WINDOW_LENGTH) / double(window->getSize().x));
	mousePosition.y = int(mousePosition.y * double(WINDOW_HIGH) / double(window->getSize().y));

	// get player position
	pair < double, double > playerPosition = player.getPositionInWindow();

	// get dist between player and mouse
	double deltX = mousePosition.x - playerPosition.first;
	double deltY = mousePosition.y - playerPosition.second;

	double len = sqrt(deltX*deltX + deltY*deltY);

	// calc speed
	return (len / TIME_GRENADE_DALAY);
}

void Grenade::move(double _timer)
{
	/*
	* function of mooving
	*
	* @param timer - how much time has been passed
	*/

	// if time for detonate
	if (timer < TIME_GRENADE_DALAY && timer + _timer > TIME_GRENADE_DALAY)
	{
		detonate = 1;
	}else
	{
		detonate = 0;
	}

	// increase timer
	timer += _timer;

	// if grenade has detonated
	if (timer > TIME_GRENADE_DALAY)
	{
		return;
	}

	// move
	positionX += cos(angle) * speed * _timer;
	positionY += sin(angle) * speed * _timer;

	return;
}

pair < double, double > Grenade::getPosition()
{
	/*
	* function of getting position
	*
	* @return position of grenade
	*/

	return { positionX, positionY };
}

int Grenade::getNumberOfPicture()
{
	/*
	* function of getting number of picture
	*
	* @return number of picture
	*/

	// if grenade has not detonated
	if (timer < TIME_GRENADE_DALAY)
	{
		return 0;
	}

	// calc number of picture
	return 1 + (int)(timer - TIME_GRENADE_DALAY) / 100;
}

bool Grenade::timeToDelete()
{
	/*
	* function of checking preparing grenade for deleting
	*
	* @return true if grenade is ready to deleting
	*/

	return timer > TIME_GRENADE_DALAY + 300;
}

bool Grenade::isDetonate()
{
	/*
	* function of getting detonate value
	*
	* @return detonate value
	*/

	return detonate;
}