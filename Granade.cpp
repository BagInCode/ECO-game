#include "Granade.h"


Granade::Granade()
{
}


Granade::~Granade()
{
}

void Granade::create(Player& player, RenderWindow* window)
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

double Granade::calculteSpeed(Player& player, RenderWindow* window)
{
	Vector2i mousePosition = Mouse::getPosition(*window);
	pair < double, double > playerPosition = player.getPositionInWindow();

	double deltX = mousePosition.x - playerPosition.first;
	double deltY = mousePosition.y - playerPosition.second;

	double len = sqrt(deltX*deltX + deltY*deltY);

	return (len / TIME_GRANADE_DALAY);
}

void Granade::move(double _timer)
{
	if (timer < TIME_GRANADE_DALAY && timer + _timer > TIME_GRANADE_DALAY)
	{
		detonate = 1;
	}else
	{
		detonate = 0;
	}

	timer += _timer;

	if (timer > TIME_GRANADE_DALAY)
	{
		return;
	}

	positionX += cos(angle) * speed * _timer;
	positionY += sin(angle) * speed * _timer;

	return;
}

pair < double, double > Granade::getPosition()
{
	return { positionX, positionY };
}

int Granade::getNumberOfPicture()
{
	if (timer < TIME_GRANADE_DALAY)
	{
		return 0;
	}

	return 1 + (int)(timer - TIME_GRANADE_DALAY) / 100;
}

bool Granade::timeToDelete()
{
	return timer > TIME_GRANADE_DALAY + 300;
}

bool Granade::isDetonate()
{
	return detonate;
}