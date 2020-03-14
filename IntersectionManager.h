#pragma once

#include "Game.h"
#include "GameEnvironmentManagerStorage.h"

class Game::IntersectionManager
{
public:
	IntersectionManager();
	~IntersectionManager();

	bool orientedArea(double x1, double y1, double x2, double y2, double x3, double y3);
	bool isIntersect(double xLeft1, double xRight1, double yUp1, double yDown1, double xLeft2, double xRight2, double yUp2, double yDown2);
	bool isInside(double x, double y, double xLeft, double xRight, double yUp, double yDown);

	pair < double, double > calculateNewPosition(double objectX, double objectY, double objectSize, double xLeft2, double xRight2, double yUp2, double yDown2);
	
	void checkIntersection(Player& player, Game* game);
	void checkIntersection(Enemy& enemy, Game* game);
	bool checkIntersection(Bullet& bullet, Game* game);

	void checkIntersection(Game* game);
};

