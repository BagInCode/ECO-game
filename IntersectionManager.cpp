#include "IntersectionManager.h"


Game::IntersectionManager::IntersectionManager()
{
}


Game::IntersectionManager::~IntersectionManager()
{
}

bool Game::IntersectionManager::orientedArea(double x1, double y1, double x2, double y2, double x3, double y3)
{
	/*
	* function of getting oriented area of triangle A(x1, y1) B(x2,y2) C(x3, y3)
	*
	* @param x1, y1, x2, y2, x3, y3 - coordinates of triangle vertex
	*
	* @return true if oriented area greather than zero
	*/

	// calculate area
	double S = x1*y2 + y1*x3 + x2*y3 - y2*x3 - x2*y1 - x1*y3;

	return (S > 0);
}

bool Game::IntersectionManager::isIntersect(double xLeft1, double xRight1, double yUp1, double yDown1, double xLeft2, double xRight2, double yUp2, double yDown2)
{
	/*
	* function of checking intersection of two rectangles
	*
	* @param xLeft1, xRight1, yUp1, yDown1 - coordinates of first rectangle
	*        xLeft2, xRight2, yUp2, yDown2 - coordinates of second rectangle
	*
	* @return true if there is intersection of two rectangles
	*/

	// calculate coordinate of intersection rectangle
	double xLeft = max(xLeft1, xLeft2);
	double xRight = min(xRight1, xRight2);
	double yUp = max(yUp1, yUp2);
	double yDown = min(yDown1, yDown2);

	// if ares of rectangle is not positive
	if (xLeft > xRight || yUp > yDown)
	{
		// there is no intersection
		return 0;
	}

	return 1;
}

bool Game::IntersectionManager::isInside(double x, double y, double xLeft, double xRight, double yUp, double yDown)
{
	/*
	* function of checking is point inside rectangle or not
	*
	* @param x,y - coordinates of point
	*        xLeft, xRight, yUp, yDown - coordinates of rectangle
	*/

	return (x > xLeft && x < xRight && y > yUp && y < yDown);
}


pair < double, double > Game::IntersectionManager::calculateNewPosition(double objectX, double objectY, double objectSize, double xLeft, double xRight, double yUp, double yDown)
{
	/*
	* function of getting new position to making no intersection
	*
	* @param objectX, objectY - coordinates of centr of mooving object
	*        objectSize - size of mooving object
	*        xLeft, xRight, yUp, yDown - coordinates of second rectangle
	*
	* @return new position of centre of mooving object to making no intersection
	*/

	// get oriented area
	bool flag1 = orientedArea(objectX, objectY, xLeft, yDown, xRight, yUp);
	bool flag2 = orientedArea(objectX, objectY, xLeft, yUp, xRight, yDown);

	// if moving up or right
	if (flag1)
	{
		// if up
		if (flag2)
		{
			return{ objectX, yDown + objectSize / 2. };
		}
		else
		{
			return{ xRight + objectSize / 2., objectY };
		}
	}
	else
	{
		// if left
		if (flag2)
		{
			return{ xLeft - objectSize / 2., objectY };
		}
		else
		{
			return{ objectX, yUp - objectSize / 2. };
		}
	}
}

void Game::IntersectionManager::checkIntersection(Player& player, Game* game)
{
	/*
	* function of checking intersection of player with trees, storages and crafting tables
	*
	* @param player - player object
	*        game - main game class
	*/

	// get size of player sprite
	double playerSize = max(player.getSize().first, player.getSize().second);

	// get coordinates of rectangle of player sprite
	double playerX1 = player.getPosition().first - playerSize / 2;
	double playerX2 = player.getPosition().first + playerSize / 2;
	double playerY1 = player.getPosition().second - playerSize / 2;
	double playerY2 = player.getPosition().second + playerSize / 2;

	// get coordinates of trees
	vector < pair < double, double  > > trees = game->environment->trees;

	// for all trees
	for (int i = 0; i < int(trees.size()); i++)
	{
		// get coordinates of vector player->tree
		double deltX = player.getPosition().first - trees[i].first;
		double deltY = player.getPosition().second - trees[i].second;

		// get size of this vector
		double dist = sqrt(deltX*deltX + deltY*deltY);

		// it player is too close to tree
		if (dist < TREE_RADIUS + playerSize)
		{
			// get angle of this vector
			double angle = atan2(deltY, deltX);

			// move player
			player.setPosition(trees[i].first + cos(angle) * (TREE_RADIUS + playerSize),
							   trees[i].second + sin(angle) * (TREE_RADIUS + playerSize));
		}
	}

	// get storages
	vector < Game::EnvironmentManager::Storage* > storages = game->environment->storages;

	// for all storages
	for (int i = 0; i < int(storages.size()); i++)
	{
		// if there is intersection of player with storage
		if (isIntersect(playerX1, playerX2, playerY1, playerY2, storages[i]->x1, storages[i]->x2, storages[i]->y1, storages[i]->y2))
		{
			pair < double, double > newPosition = calculateNewPosition(player.getPosition().first, player.getPosition().second, playerSize, 
																	   storages[i]->x1, storages[i]->x2, storages[i]->y1, storages[i]->y2);

			player.setPosition(newPosition.first, newPosition.second);
		}
	}

	// get crafting tables
	vector < pair < pair < double, double >, pair < double, double > > > craftingTables = game->environment->craftingTables;

	// for all craftings tables
	for (int i = 0; i < int(craftingTables.size()); i++)
	{
		// if there is intersection of player with crafting table
		if (isIntersect(playerX1, playerX2, playerY1, playerY2, 
						craftingTables[i].first.first, craftingTables[i].first.second, craftingTables[i].second.first, craftingTables[i].second.second))
		{
			pair < double, double > newPosition = calculateNewPosition(player.getPosition().first, player.getPosition().second, playerSize,
				craftingTables[i].first.first, craftingTables[i].first.second, craftingTables[i].second.first, craftingTables[i].second.second);

			player.setPosition(newPosition.first, newPosition.second);
		}
	}

	return;
}

void Game::IntersectionManager::checkIntersection(Enemy& enemy, Game* game)
{
	/*
	* function of checking intersection of enemy with trees, storages and crafting tables
	*
	* @param player - player object
	*        game - main game class
	*/

	// get size of player sprite
	double enemySize = max(enemy.getSize().first, enemy.getSize().second);

	// get coordinates of rectangle of player sprite
	double enemyX1 = enemy.getPosition().first - enemySize / 2;
	double enemyX2 = enemy.getPosition().first + enemySize / 2;
	double enemyY1 = enemy.getPosition().second - enemySize / 2;
	double enemyY2 = enemy.getPosition().second + enemySize / 2;

	// get coordinates of trees
	vector < pair < double, double  > > trees = game->environment->trees;

	// for all trees
	for (int i = 0; i < int(trees.size()); i++)
	{
		// get coordinates of vector player->tree
		double deltX = enemy.getPosition().first - trees[i].first;
		double deltY = enemy.getPosition().second - trees[i].second;

		// get size of this vector
		double dist = sqrt(deltX*deltX + deltY*deltY);

		// it player is too close to tree
		if (dist < TREE_RADIUS + enemySize)
		{
			// get angle of this vector
			double angle = atan2(deltY, deltX);

			// move player
			enemy.setPosition(trees[i].first + cos(angle) * (TREE_RADIUS + enemySize),
				trees[i].second + sin(angle) * (TREE_RADIUS + enemySize));
		}
	}

	// get storages
	vector < Game::EnvironmentManager::Storage* > storages = game->environment->storages;

	// for all storages
	for (int i = 0; i < int(storages.size()); i++)
	{
		// if there is intersection of player with storage
		if (isIntersect(enemyX1, enemyX2, enemyY1, enemyY2, storages[i]->x1, storages[i]->x2, storages[i]->y1, storages[i]->y2))
		{
			pair < double, double > newPosition = calculateNewPosition(enemy.getPosition().first, enemy.getPosition().second, enemySize,
				storages[i]->x1, storages[i]->x2, storages[i]->y1, storages[i]->y2);

			enemy.setPosition(newPosition.first, newPosition.second);
		}
	}

	// get crafting tables
	vector < pair < pair < double, double >, pair < double, double > > > craftingTables = game->environment->craftingTables;

	// for all craftings tables
	for (int i = 0; i < int(craftingTables.size()); i++)
	{
		// if there is intersection of player with crafting table
		if (isIntersect(enemyX1, enemyX2, enemyY1, enemyY2,
			craftingTables[i].first.first, craftingTables[i].first.second, craftingTables[i].second.first, craftingTables[i].second.second))
		{
			pair < double, double > newPosition = calculateNewPosition(enemy.getPosition().first, enemy.getPosition().second, enemySize,
				craftingTables[i].first.first, craftingTables[i].first.second, craftingTables[i].second.first, craftingTables[i].second.second);

			enemy.setPosition(newPosition.first, newPosition.second);
		}
	}

	return;
}

bool Game::IntersectionManager::checkIntersection(Bullet& bullet, Game* game)
{
	/*
	* function of checking intersection of bullet with player, enemy, trees, storages and crafting tables
	*
	* @param player - player object
	*        game - main game class
	*
	* @return true if bullet has intersection with some objects
	*/

	// get bullet previous position
	pair < double, double > previousPosition = bullet.getPreviousPosition();
	
	// get bullet current position
	pair < double, double > currentPosition = bullet.getPosition();

	// get delt between positions
	double deltX = (currentPosition.first - previousPosition.first) / COUNT_SEGMENTS_FOR_BULLET_CHECKING;
	double deltY = (currentPosition.second - previousPosition.second) / COUNT_SEGMENTS_FOR_BULLET_CHECKING;

	// remember here positions for checking
	vector < pair < double, double > > positionsForChecking;

	// remember it
	for (int i = 0; i < COUNT_SEGMENTS_FOR_BULLET_CHECKING; i++)
	{
		positionsForChecking.push_back({ previousPosition.first + (i + 1)*deltX, previousPosition.second + (i + 1)*deltY });
	}

	// get position of trees
	vector < pair < double, double > > trees = game->environment->trees;

	// for all trees
	for (int i = 0; i < int(trees.size()); i++)
	{
		// for all positions for checking
		for (int j = 0; j < int(positionsForChecking.size()); j++)
		{
			double deltX = positionsForChecking[j].first - trees[i].first;
			double deltY = positionsForChecking[j].second - trees[i].second;

			// calculate dist between tree and bullet
			double dist = sqrt(deltX*deltX + deltY*deltY);

			// if bullet is inside the tree
			if (dist < TREE_RADIUS)
			{
				// bullet has intersection
				return 1;
			}
		}
	}

	// get storages
	vector < Game::EnvironmentManager::Storage* > storages = game->environment->storages;

	// for all storages
	for (int i = 0; i < int(storages.size()); i++)
	{
		// for all positions for checking
		for (int j = 0; j < int(positionsForChecking.size()); j++)
		{
			// if bullet is inside the storage
			if (isInside(positionsForChecking[j].first, positionsForChecking[j].second, 
				storages[i]->x1, storages[i]->x2, storages[i]->y1, storages[i]->y2))
			{
				// bullet has intersection
				return 1;
			}
		}
	}

	// get crafting tables
	vector < pair < pair < double, double >, pair < double, double > > > craftingTables = game->environment->craftingTables;

	// for all crafting tables
	for (int i = 0; i < int(craftingTables.size()); i++)
	{
		// for all positions for checking
		for (int j = 0; j < int(positionsForChecking.size()); j++)
		{
			// if bullet is inside the crafting tables
			if (isInside(positionsForChecking[j].first, positionsForChecking[j].second,
				craftingTables[i].first.first, craftingTables[i].first.second, craftingTables[i].second.first, craftingTables[i].second.second))
			{
				// bullet has intersetion
				return 1;
			}
		}
	}

	// if player is target
	if (bullet.getIsPlayerTarget())
	{
		// get rectangle of player body
		double xLeft = game->playerObject.getPosition().first - CHARACTER_BODY_RADIUS;
		double xRight = game->playerObject.getPosition().first + CHARACTER_BODY_RADIUS;
		double yUp = game->playerObject.getPosition().second - CHARACTER_BODY_RADIUS;
		double yDown = game->playerObject.getPosition().second + CHARACTER_BODY_RADIUS;

		// for all positions for checking
		for (int i = 0; i < int(positionsForChecking.size()); i++)
		{
			// if bullet is inside the player
			if (isInside(positionsForChecking[i].first, positionsForChecking[i].second, xLeft, xRight, yUp, yDown))
			{
				// decrease player HP
				game->playerObject.getDamage(bullet.getDamage());

				// bulet has intersection
				return 1;
			}
		}
	}
	else
	{
		// for all enemys
		for (int i = 0; i < int(game->Enemys.size()); i++)
		{
			// get rectangle of enemy body
			double xLeft = game->Enemys[i].getPosition().first - CHARACTER_BODY_RADIUS;
			double xRight = game->Enemys[i].getPosition().first + CHARACTER_BODY_RADIUS;
			double yUp = game->Enemys[i].getPosition().second - CHARACTER_BODY_RADIUS;
			double yDown = game->Enemys[i].getPosition().second + CHARACTER_BODY_RADIUS;

			// for all positions for checking
			for (int j = 0; j < int(positionsForChecking.size()); j++)
			{
				// if bullet is inside the enemy
				if (isInside(positionsForChecking[j].first, positionsForChecking[j].second, xLeft, xRight, yUp, yDown))
				{
					// decrease enemy HP
					game->Enemys[i].getDamage(bullet.getDamage());

					// bulet has intersection
					return 1;
				}
			}
		}
	}

	// bullet has no intersection
	return 0;
}

void Game::IntersectionManager::checkIntersection(Game* game)
{
	/*
	* function of checking intersection of mooving objects
	*
	* @param game - main game class
	*/

	// check intersection of player
	checkIntersection(game->playerObject, game);

	// for all enemys
	for (int i = 0; i < int(game->Enemys.size()); i++)
	{
		// check intersection
		checkIntersection(game->Enemys[i], game);
	}

	// create new bullets vector
	vector < Bullet > newBullets;

	// for all bullets
	for (int i = 0; i < int(game->Bullets.size()); i++)
	{
		// if bullet has no intersection with other object and there is not time for delete this bullet
		if (!checkIntersection(game->Bullets[i], game) && !game->Bullets[i].readyToDelete())
		{
			// add to bullets vector
			newBullets.push_back(game->Bullets[i]);
		}
	}

	// overwrite previous vector
	game->Bullets = newBullets;
}