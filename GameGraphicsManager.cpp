#include "Game.h"
#include "GameGraphicsManager.h"


bool Game::GraphicsManager::loadSprites()
{
	/*
	* function of loading sprites
	*
	* @return true - if loadding complited
	*         false - if loading failed
	*/

	// if texture does not load 
	if (!environmentTexture.loadFromFile(ENVIROMENT_TEXTURE_FILE_PATH))
	{
		// loading failed
		return 0;
	}

	// choose image of ground
	groundSprite.setTexture(environmentTexture);
	groundSprite.setTextureRect(IntRect(0, 0, SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL));

	// choose image of storage
	storageSprite.setTexture(environmentTexture);
	storageSprite.setTextureRect(IntRect(HAUSE_SPRITE_POSITION_LEFT, HAUSE_SPRITE_POSITION_TOP, HAUSE_SPRITE_LENGTH, HAUSE_SPRITE_HIGH));

	// choose image of bullet
	bulletSprite.setTexture(environmentTexture);
	bulletSprite.setTextureRect(IntRect(0, 0, 3, 3));
	bulletSprite.setColor(Color::Red);

	// choose image of player pistol sprite
	playerSprite = &playerPistolSprite;


	// choose image of player pistol sprite
	playerPistolSprite.setTexture(environmentTexture);
	playerPistolSprite.setTextureRect(IntRect(PLAYER_SPRITE_PISTOL_LEFT, PLAYER_SPRITE_PISTOL_TOP, PLAYER_SPRITE_AK_LENGTH, PLAYER_SPRITE_AK_HIGH));
	playerPistolSprite.setOrigin(PLAYER_SPRITE_AK_LENGTH / 2., PLAYER_SPRITE_AK_HIGH / 2.);

	// choose image of player shotgun sprite
	playerShotgunSprite.setTexture(environmentTexture);
	playerShotgunSprite.setTextureRect(IntRect(PLAYER_SPRITE_HUNTER_LEFT, PLAYER_SPRITE_HUNTER_TOP, PLAYER_SPRITE_AK_LENGTH, PLAYER_SPRITE_AK_HIGH));
	playerShotgunSprite.setOrigin(PLAYER_SPRITE_AK_LENGTH / 2., PLAYER_SPRITE_AK_HIGH / 2.);

	// choose image of player rifle sprite
	playerRifleSprite.setTexture(environmentTexture);
	playerRifleSprite.setTextureRect(IntRect(PLAYER_SPRITE_AK_POSITION_LEFT, PLAYER_SPRITE_AK_POSITION_TOP, PLAYER_SPRITE_AK_LENGTH, PLAYER_SPRITE_AK_HIGH));
	playerRifleSprite.setOrigin(PLAYER_SPRITE_AK_LENGTH / 2., PLAYER_SPRITE_AK_HIGH / 2.);

	// choose image rectangle of player minigun sprite
	playerMachinGunSprite.setTexture(environmentTexture);
	playerMachinGunSprite.setTextureRect(IntRect(PLAYER_SPRITE_MINIGUN_LEFT, PLAYER_SPRITE_MINIGUN_TOP, PLAYER_SPRITE_AK_LENGTH, PLAYER_SPRITE_AK_HIGH));
	playerMachinGunSprite.setOrigin(PLAYER_SPRITE_AK_LENGTH / 2., PLAYER_SPRITE_AK_HIGH / 2.);

	// choose image rectangle of player sniper sprite
	playerSniperRifleSprite.setTexture(environmentTexture);
	playerSniperRifleSprite.setTextureRect(IntRect(PLAYER_SPRITE_SNIPER_LEFT, PLAYER_SPRITE_SNIPER_TOP, PLAYER_SNIPER_LENGTH, PLAYER_SPRITE_AK_HIGH));
	playerSniperRifleSprite.setOrigin(PLAYER_SNIPER_LENGTH / 2., PLAYER_SPRITE_AK_HIGH / 2.);

	// choose image of enemy
	enemySprite.setTexture(environmentTexture);
	enemySprite.setTextureRect(IntRect(ENEMY_SPRITE_LEFT, ENEMY_SPRITE_TOP, ENEMY_SPRITE_LENGTH, ENEMY_SPRITE_HIGH));
	enemySprite.setOrigin(ENEMY_SPRITE_LENGTH / 2., ENEMY_SPRITE_HIGH / 2.);

	// choose image of tree
	treeSprite.setTexture(environmentTexture);
	treeSprite.setTextureRect(IntRect(TREE_SPRITE_POSITION_LEFT, TREE_SPRITE_POSITION_TOP, SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL));


	// if texture does not load
	if (!minimapTexture.loadFromFile(MINIMAP_TEXTURE_FILE_PATH))
	{
		// loading failed
		return 0;
	}

	// set image of active ground
	minimapActiveGroundSprite.setTexture(minimapTexture);
	minimapActiveGroundSprite.setTextureRect(IntRect(MINIMAP_GROUND_ACTIVE_SPRITE_LEFT, MINIMAP_GROUND_ACTIVE_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// set image of active house
	minimapActiveHouseSprite.setTexture(minimapTexture);
	minimapActiveHouseSprite.setTextureRect(IntRect(MINIMAP_HOUSE_ACTIVE_SPRITE_LEFT, MINIMAP_HOUSE_ACTIVE_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// set image of active tree
	minimapActiveTreeSprite.setTexture(minimapTexture);
	minimapActiveTreeSprite.setTextureRect(IntRect(MINIMAP_TREE_ACTIVE_SPRITE_LEFT, MINIMAP_TREE_ACTIVE_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// set image of player
	minimapPlayerSprite.setTexture(minimapTexture);
	minimapPlayerSprite.setTextureRect(IntRect(MINIMAP_PLAYER_SPRITE_LEFT, MINIMAP_PLAYER_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// set image of enemy
	minimapEnemySprite.setTexture(minimapTexture);
	minimapEnemySprite.setTextureRect(IntRect(MINIMAP_ENEMY_SPRITE_LEFT, MINIMAP_ENEMY_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// set image of invisible
	minimapInvisibleSprite.setTexture(minimapTexture);
	minimapInvisibleSprite.setTextureRect(IntRect(MINIMAP_INVISIBLE_SPRITE_LEFT, MINIMAP_INVISIBLE_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// set image of inactive ground
	minimapInactiveGroundSprite.setTexture(minimapTexture);
	minimapInactiveGroundSprite.setTextureRect(IntRect(MINIMAP_GROUND_INACTIVE_SPRITE_LEFT, MINIMAP_GROUND_INACTIVE_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// set image of inactive house
	minimapInactiveHouseSprite.setTexture(minimapTexture);
	minimapInactiveHouseSprite.setTextureRect(IntRect(MINIMAP_HOUSE_INACTIVE_SPRITE_LEFT, MINIMAP_HOUSE_INACTIVE_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// set image of inactive tree
	minimapInactiveTreeSprite.setTexture(minimapTexture);
	minimapInactiveTreeSprite.setTextureRect(IntRect(MINIMAP_TREE_INACTIVE_SPRITE_LEFT, MINIMAP_TREE_INACTIVE_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	return 1;
}

void Game::GraphicsManager::drawPicture(Game* game)
{
	/*
	* function of drawing picture in game window
	*/

	// clear previous picture, set color of background black
	game->window->clear(Color::Black);

	// get position of player sprite inside game window
	double playerPositionX = game->playerObject.getPositionInWindow().first;
	double playerPositionY = game->playerObject.getPositionInWindow().second;

	// get position of player sprite on map
	double playerGlobalPositionX = game->playerObject.getPosition().first;
	double playerGlobalPositionY = game->playerObject.getPosition().second;

	// get position in array of cell, where player stay
	int playerCellX = playerGlobalPositionX / SQUARE_SIZE_PIXIL;
	int playerCellY = playerGlobalPositionY / SQUARE_SIZE_PIXIL;

	// calculate borders of drawing rectangle
	int Left = max(0, playerCellX - 15);
	int Right = min(FIELD_SIZE - 1, playerCellX + 15);
	int Up = max(0, playerCellY - 10);
	int Down = min(FIELD_SIZE - 1, playerCellY + 10);

	//vector < vector < pair < double, double > > > drawingOrder;
	vector<pair<double, double> > groundsToDraw;
	vector <int> storagesToDraw;
	vector<pair<double, double> > bulletsToDraw;
	vector<pair<double, double> > enemiesToDraw;
	vector<pair<double, double> > treesToDraw;

	for (int i = Up; i <= Down; i++)
	{
		for (int j = Left; j <= Right; j++)
		{
			// get global position of cell
			double cellPositionX = j * SQUARE_SIZE_PIXIL;
			double cellPositionY = i * SQUARE_SIZE_PIXIL;

			// get difference between player and cell global positions
			double deltX = cellPositionX - playerGlobalPositionX;
			double deltY = cellPositionY - playerGlobalPositionY;

			// add ground to drawing order
			groundsToDraw.push_back({ playerPositionX + deltX, playerPositionY + deltY });

			// if there is smth in this square
			if (game->Field[i][j] == 5)
			{
				// add to the order
				treesToDraw.push_back({ playerPositionX + deltX, playerPositionY + deltY });
			}

			if (game->storageNumber[i][j] != -1)
			{
				storagesToDraw.push_back(game->storageNumber[i][j]);
			}
		}
	}

	// for all Bullets
	for (int i = 0; i < game->Bullets.size(); i++)
	{
		// get Bullet position
		double bulletPositionX = game->Bullets[i].getPosition().first;
		double bulletPositionY = game->Bullets[i].getPosition().second;

		// get difference
		double deltX = bulletPositionX - playerGlobalPositionX;
		double deltY = bulletPositionY - playerGlobalPositionY;

		// add to order
		bulletsToDraw.push_back({ playerPositionX + deltX, playerPositionY + deltY });
	}

	// get angle of player sprite
	double angle = game->playerObject.rotate(game->window);
	playerSprite->setRotation(angle * 180 / acos(-1));

	if (game->playerObject.isDamaged > 0)
	{
		playerSprite->setColor(Color::Red);
	}

	// add enemys
	for (int i = 0; i < game->Enemys.size(); i++)
	{
		pair < double, double > position;

		// calculate position in window
		position.first = playerPositionX + game->Enemys[i].getPosition().first - playerGlobalPositionX;
		position.second = playerPositionY + game->Enemys[i].getPosition().second - playerGlobalPositionY;

		// add to order
		enemiesToDraw.push_back(position);
	}


	// for each type of sprites

	// draw grounds
	for (int j = 0; j < groundsToDraw.size(); j++)
	{
		groundSprite.setPosition(groundsToDraw[j].first, groundsToDraw[j].second);
		game->window->draw(groundSprite);
	}

	// draw storages
	for (auto& storageI : storagesToDraw)
	{
		game->storages[storageI].draw(game->window, playerGlobalPositionX - playerPositionX, playerGlobalPositionY - playerPositionY,
			playerGlobalPositionX, playerGlobalPositionY, storageSprite);
	}

	// draw bullets
	for (int j = 0; j < bulletsToDraw.size(); j++)
	{
		bulletSprite.setPosition(bulletsToDraw[j].first, bulletsToDraw[j].second);
		game->window->draw(bulletSprite);
	}

	// draw player
	playerSprite->setPosition(game->playerObject.getPositionInWindow().first, game->playerObject.getPositionInWindow().second);
	game->window->draw(*playerSprite);

	// draw enemys
	for (int j = 0; j < enemiesToDraw.size(); j++)
	{
		enemySprite.setPosition(enemiesToDraw[j].first, enemiesToDraw[j].second);
		enemySprite.setRotation(game->Enemys[j].getAngleWatching() * 180 / acos(-1));
		game->window->draw(enemySprite);
	}

	// draw trees
	for (int j = 0; j < treesToDraw.size(); j++)
	{
		treeSprite.setPosition(treesToDraw[j].first, treesToDraw[j].second);
		game->window->draw(treeSprite);
	}

	// set base color to player sprite
	playerSprite->setColor(Color::White);

	// showing picture
	game->window->display();

	return;
}

void Game::GraphicsManager::drawMinimap(Game* game)
{
	/*
	* function of drawing minimap
	*
	*/

	// clear window, set color of background black
	game->window->clear(Color::Black);

	// get position of player square
	int playerX = game->playerObject.getPosition().first / SQUARE_SIZE_PIXIL;
	int playerY = game->playerObject.getPosition().second / SQUARE_SIZE_PIXIL;

	// for all square
	Sprite* spritePointer = nullptr;
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			// if not opened square
			if (!game->visionMap[i][j])
			{
				// set pointer to invisible sprite
				spritePointer = &minimapInvisibleSprite;
			}
			else
			{
				if (game->isVisible(playerX, playerY, j, i))
				{
					// if ground -> set pointer to the ground
					if (game->Field[i][j] == 0)
					{
						spritePointer = &minimapActiveGroundSprite;
					}// if house -> set pointer to the house
					else if (game->Field[i][j] == -1)
					{
						spritePointer = &minimapActiveHouseSprite;
					}// if tree -> set pointer to the tree
					else if (game->Field[i][j] == 5)
					{
						spritePointer = &minimapActiveTreeSprite;
					}
				}
				else
				{
					// if ground -> set pointer to the ground
					if (game->Field[i][j] == 0)
					{
						spritePointer = &minimapInactiveGroundSprite;
					}// if house -> set pointer to the house
					else if (game->Field[i][j] == -1)
					{
						spritePointer = &minimapInactiveHouseSprite;
					}// if tree -> set pointer to the tree
					else if (game->Field[i][j] == 5)
					{
						spritePointer = &minimapInactiveTreeSprite;
					}
				}
			}

			// set position
			spritePointer->setPosition(MINIMAP_DELT_X + j * MINIMAP_SQUARE_SIZE_PIXIL, i * MINIMAP_SQUARE_SIZE_PIXIL);

			// draw
			game->window->draw(*spritePointer);
		}
	}

	// fro all enemys
	for (int i = 0; i < game->Enemys.size(); i++)
	{
		// get cordinates of square
		int enemyX = game->Enemys[i].getPosition().first / SQUARE_SIZE_PIXIL;
		int enemyY = game->Enemys[i].getPosition().second / SQUARE_SIZE_PIXIL;

		// if square is not visible
		if (!game->isVisible(playerX, playerY, enemyX, enemyY))
		{
			// go to next enemy
			continue;
		}

		// set position
		minimapEnemySprite.setPosition(MINIMAP_DELT_X + enemyX * MINIMAP_SQUARE_SIZE_PIXIL, enemyY * MINIMAP_SQUARE_SIZE_PIXIL);

		// draw
		game->window->draw(minimapEnemySprite);
	}

	// set player sprite position
	minimapPlayerSprite.setPosition(MINIMAP_DELT_X + playerX * MINIMAP_SQUARE_SIZE_PIXIL, playerY * MINIMAP_SQUARE_SIZE_PIXIL);
	game->window->draw(minimapPlayerSprite);

	// sho picture
	game->window->display();

	return;
}