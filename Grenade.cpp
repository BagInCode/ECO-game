#include "Grenade.h"


Grenade::Grenade()
{
}


Grenade::~Grenade()
{
}

void Grenade::create(Player& player, RenderWindow* window)
{
	angle = player.getAngle();
	positionX = player.getPosition().first;
	positionY = player.getPosition().second;

	speed = calculteSpeed(player, window);

	timer = 0;
	numberPictureToDraw = 0;
	detonate = 0;

	return;
}

double Grenade::calculteSpeed(Player& player, RenderWindow* window)
{
	Vector2i mousePosition = Mouse::getPosition(*window);
	mousePosition.x *= double(WINDOW_LENGTH) / double(window->getSize().x);
	mousePosition.y *= double(WINDOW_HIGH) / double(window->getSize().y);


	pair < double, double > playerPosition = player.getPositionInWindow();

	double deltX = mousePosition.x - playerPosition.first;
	double deltY = mousePosition.y - playerPosition.second;

	double len = sqrt(deltX*deltX + deltY*deltY);

	return (len / TIME_GRENADE_DALAY);
}

void Grenade::move(double _timer)
{
	if (timer < TIME_GRENADE_DALAY && timer + _timer > TIME_GRENADE_DALAY)
	{
		detonate = 1;
	}else
	{
		detonate = 0;
	}

	timer += _timer;

	if (timer > TIME_GRENADE_DALAY)
	{
		return;
	}

	positionX += cos(angle) * speed * _timer;
	positionY += sin(angle) * speed * _timer;

	return;
}

pair < double, double > Grenade::getPosition()
{
	return { positionX, positionY };
}

int Grenade::getNumberOfPicture()
{
	if (timer < TIME_GRENADE_DALAY)
	{
		return 0;
	}

	return 1 + (int)(timer - TIME_GRENADE_DALAY) / 100;
}

bool Grenade::timeToDelete()
{
	return timer > TIME_GRENADE_DALAY + 300;
}

bool Grenade::isDetonate()
{
	return detonate;
}