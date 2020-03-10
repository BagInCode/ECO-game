#include "GameGraphicsManagerMinimap.h"
#include "GameEnvironmentManager.h"

void Game::GraphicsManager::Minimap::initComponents()
{
	loadSprites();

	for (auto& it : visionMap)
	{
		for (auto& itt : it)
		{
			itt = false;
		}
	}
}

void Game::GraphicsManager::Minimap::loadSprites()
{
	minimapTexture.loadFromFile(MINIMAP_TEXTURE_FILE_PATH);

	// set image of active ground
	activeGroundSprite.setTexture(minimapTexture);
	activeGroundSprite.setTextureRect(IntRect(MINIMAP_GROUND_ACTIVE_SPRITE_LEFT, MINIMAP_GROUND_ACTIVE_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// set image of active house
	activeHouseSprite.setTexture(minimapTexture);
	activeHouseSprite.setTextureRect(IntRect(MINIMAP_HOUSE_ACTIVE_SPRITE_LEFT, MINIMAP_HOUSE_ACTIVE_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// set image of active tree
	activeTreeSprite.setTexture(minimapTexture);
	activeTreeSprite.setTextureRect(IntRect(MINIMAP_TREE_ACTIVE_SPRITE_LEFT, MINIMAP_TREE_ACTIVE_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// set image of player
	playerSprite.setTexture(minimapTexture);
	playerSprite.setTextureRect(IntRect(MINIMAP_PLAYER_SPRITE_LEFT, MINIMAP_PLAYER_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// set image of enemy
	enemySprite.setTexture(minimapTexture);
	enemySprite.setTextureRect(IntRect(MINIMAP_ENEMY_SPRITE_LEFT, MINIMAP_ENEMY_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// set image of invisible
	invisibleSprite.setTexture(minimapTexture);
	invisibleSprite.setTextureRect(IntRect(MINIMAP_INVISIBLE_SPRITE_LEFT, MINIMAP_INVISIBLE_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// set image of inactive ground
	inactiveGroundSprite.setTexture(minimapTexture);
	inactiveGroundSprite.setTextureRect(IntRect(MINIMAP_GROUND_INACTIVE_SPRITE_LEFT, MINIMAP_GROUND_INACTIVE_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// set image of inactive house
	inactiveHouseSprite.setTexture(minimapTexture);
	inactiveHouseSprite.setTextureRect(IntRect(MINIMAP_HOUSE_INACTIVE_SPRITE_LEFT, MINIMAP_HOUSE_INACTIVE_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// set image of inactive tree
	inactiveTreeSprite.setTexture(minimapTexture);
	inactiveTreeSprite.setTextureRect(IntRect(MINIMAP_TREE_INACTIVE_SPRITE_LEFT, MINIMAP_TREE_INACTIVE_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	craftingTableTexture.loadFromFile("Textures\\craftingTableMinimap.png");
	activeCraftingTableSprite.setTexture(craftingTableTexture);
	activeCraftingTableSprite.setTextureRect(IntRect(0, 0, 7, 7));
	inactiveCraftingTableSprite.setTexture(craftingTableTexture);
	inactiveCraftingTableSprite.setTextureRect(IntRect(0, 7, 7, 7));
}

void Game::GraphicsManager::Minimap::update(Game* game)
{
	updateVision(game);
}

void Game::GraphicsManager::Minimap::updateVision(Game* game)
{
	/*
	* function of updating minimap vision
	*/

	// get position of player square
	int playerX = int(game->playerObject.getPosition().first) / SQUARE_SIZE_PIXIL;
	int playerY = int(game->playerObject.getPosition().second) / SQUARE_SIZE_PIXIL;

	// get coordinate of square
	int Up = min(FIELD_SIZE - 1, playerY + MAX_VISIBLE_DIST);
	int Down = max(0, playerY - MAX_VISIBLE_DIST);
	int Left = max(playerX - MAX_VISIBLE_DIST, 0);
	int Right = min(playerX + MAX_VISIBLE_DIST, FIELD_SIZE - 1);

	// for each square
	for (int i = Down; i <= Up; i++)
	{
		for (int j = Left; j <= Right; j++)
		{
			// set visibility
			visionMap[i][j] = 1;
		}
	}
}

bool Game::GraphicsManager::Minimap::isVisible(int playerX, int playerY, int x, int y)
{
	/*
	* function of checking is square visible for player
	*
	* @param playerX, playerY - coordinate of player square
	*        x, y - coordinate of square for checking
	*
	* @return true - if square is visible for player
	*/

	return (abs(playerX - x) <= MAX_VISIBLE_DIST) && (abs(playerY - y) <= MAX_VISIBLE_DIST);
}

void Game::GraphicsManager::Minimap::draw(Game* game)
{
	/*
	* function of drawing minimap
	*
	*/

	// clear window, set color of background black
	game->window->clear(Color::Black);

	// get position of player square
	int playerX = int(game->playerObject.getPosition().first) / SQUARE_SIZE_PIXIL;
	int playerY = int(game->playerObject.getPosition().second) / SQUARE_SIZE_PIXIL;

	// for all square
	Sprite* spritePointer = nullptr;
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			// if not opened square
			if (!visionMap[i][j])
			{
				// set pointer to invisible sprite
				spritePointer = &invisibleSprite;
			}
			else
			{
				if (isVisible(playerX, playerY, j, i))
				{
					// if ground -> set pointer to the ground
					if (game->environment->field[i][j] == 0)
					{
						spritePointer = &activeGroundSprite;
					}// if house -> set pointer to the house
					else if (game->environment->field[i][j] == -1)
					{
						spritePointer = &activeHouseSprite;
					}// if tree -> set pointer to the tree
					else if (game->environment->field[i][j] == 5)
					{
						spritePointer = &activeTreeSprite;
					}
					else if (game->environment->field[i][j] == 4)
					{
						spritePointer = &activeCraftingTableSprite;
					}
				}
				else
				{
					// if ground -> set pointer to the ground
					if (game->environment->field[i][j] == 0)
					{
						spritePointer = &inactiveGroundSprite;
					}// if house -> set pointer to the house
					else if (game->environment->field[i][j] == -1)
					{
						spritePointer = &inactiveHouseSprite;
					}// if tree -> set pointer to the tree
					else if (game->environment->field[i][j] == 5)
					{
						spritePointer = &inactiveTreeSprite;
					}
					else if (game->environment->field[i][j] == 4)
					{
						spritePointer = &inactiveCraftingTableSprite;
					}
				}
			}

			// set position
			spritePointer->setPosition(MINIMAP_DELT_X + j * float(MINIMAP_SQUARE_SIZE_PIXIL), i * float(MINIMAP_SQUARE_SIZE_PIXIL));

			// draw
			game->window->draw(*spritePointer);
		}
	}

	// fro all enemys
	for (int i = 0; i < int(game->Enemys.size()); i++)
	{
		// get cordinates of square
		int enemyX = int(game->Enemys[i].getPosition().first / SQUARE_SIZE_PIXIL);
		int enemyY = int(game->Enemys[i].getPosition().second / SQUARE_SIZE_PIXIL);

		// if square is not visible
		if (!isVisible(playerX, playerY, enemyX, enemyY))
		{
			// go to next enemy
			continue;
		}

		// set position
		enemySprite.setPosition(MINIMAP_DELT_X + enemyX * float(MINIMAP_SQUARE_SIZE_PIXIL), enemyY * float(MINIMAP_SQUARE_SIZE_PIXIL));

		// draw
		game->window->draw(enemySprite);
	}

	// set player sprite position
	playerSprite.setPosition(MINIMAP_DELT_X + playerX * float(MINIMAP_SQUARE_SIZE_PIXIL), playerY * float(MINIMAP_SQUARE_SIZE_PIXIL));
	game->window->draw(playerSprite);
}