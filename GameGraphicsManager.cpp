#include "Game.h"
#include "GameGraphicsManager.h"
#include "GameGraphicsManagerInterface.h"
#include "GameGraphicsManagerMinimap.h"
#include "GameGraphicsManagerCraftingTable.h"
#include "GameEnvironmentManager.h"
#include "GameEnvironmentManagerStorage.h"

Game::GraphicsManager::GraphicsManager()
{
	interface = new GraphicsManager::Interface;
	minimap = new Minimap;
	craftingTable = new CraftingTable;
}

Game::GraphicsManager::~GraphicsManager()
{
	delete interface;
	delete minimap;
	delete craftingTable;
}

void Game::GraphicsManager::update(Game* game, double timer)
{
	interface->update(game, timer);
	minimap->update(game);

	if (drawSwitcher == 2)
	{
		craftingTable->update(game);
	}
}

void Game::GraphicsManager::initComponents(Game* game)
{
	loadStorageFonts(game);

	interface->initComponents();
	minimap->initComponents();
	craftingTable->initComponents(game);

	loadSprites();

	drawSwitcher = 0;
}

bool Game::GraphicsManager::loadSprites()
{
	/*
	* function of loading sprites
	*
	* @return true - if loadding complited
	*         false - if loading failed
	*/

	// if texture does not load 
	if (!environmentTexture.loadFromFile(ENVIRONMENT_TEXTURE_FILE_PATH))
	{
		// loading failed
		return 0;
	}

	// choose image of ground
	groundSprite.setTexture(environmentTexture);
	groundSprite.setTextureRect(IntRect(0, 0, SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL));

	// choose image of closed storage
	storageSprite[0].setTexture(environmentTexture);
	storageSprite[0].setTextureRect(IntRect(HANGAR_SPRITE_CLOSE_POSITION_LEFT, HANGAR_SPRITE_CLOSE_POSITION_TOP, HANGAR_SPRITE_LENGTH, HANGAR_SPRITE_HIGH));

	// choose image of open storage
	storageSprite[1].setTexture(environmentTexture);
	storageSprite[1].setTextureRect(IntRect(HANGAR_SPRITE_OPEN_POSITION_LEFT, HANGAR_SPRITE_OPEN_POSITION_TOP, HANGAR_SPRITE_LENGTH, HANGAR_SPRITE_HIGH));

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

	// choose image of granade
	grenadeSprite[0].setTexture(environmentTexture);
	grenadeSprite[0].setTextureRect(IntRect(GRENADE_SPRITE_POSITION_LEFT, GRENADE_SPRITE_POSITION_TOP, GRENADE_SPRITE_LENGTH, GRENADE_SPRITE_HIGH));
	grenadeSprite[0].setOrigin(GRENADE_SPRITE_LENGTH / 2, GRENADE_SPRITE_HIGH / 2);

	// choose inmage of fire
	grenadeSprite[1].setTexture(environmentTexture);
	grenadeSprite[1].setTextureRect(IntRect(FIRST_FIRE_SPRITE_POSITION_LEFT, FIRST_FIRE_SPRITE_POSITION_TOP, FIRST_FIRE_SPRITE_LENGTH, FIRST_FIRE_SPRITE_HIGH));
	grenadeSprite[1].setOrigin(SECOND_FIRE_SPRITE_LENGTH / 2, FIRST_FIRE_SPRITE_HIGH / 2);

	// choose inmage of fire
	grenadeSprite[2].setTexture(environmentTexture);
	grenadeSprite[2].setTextureRect(IntRect(SECOND_FIRE_SPRITE_POSITION_LEFT, SECOND_FIRE_SPRITE_POSITION_TOP, SECOND_FIRE_SPRITE_LENGTH, SECOND_FIRE_SPRITE_HIGH));
	grenadeSprite[2].setOrigin(SECOND_FIRE_SPRITE_LENGTH / 2, SECOND_FIRE_SPRITE_HIGH / 2);

	// choose inmage of fire
	grenadeSprite[3].setTexture(environmentTexture);
	grenadeSprite[3].setTextureRect(IntRect(THIRD_FIRE_SPRITE_POSITION_LEFT, THIRD_FIRE_SPRITE_POSITION_TOP, THIRD_FIRE_SPRITE_LENGTH, THIRD_FIRE_SPRITE_HIGH));
	grenadeSprite[3].setOrigin(THIRD_FIRE_SPRITE_LENGTH / 2, THIRD_FIRE_SPRITE_HIGH / 2);

	// choose image of crafting table
	craftingTableSprite.setTexture(environmentTexture);
	craftingTableSprite.setTextureRect(IntRect(CRAFTING_TABLE_POSITION_LEFT, CRAFTING_TABLE_POSITION_TOP, CRAFTING_TABLE_LENGTH, CRAFTING_TABLE_HIGH));

	return 1;
}

void Game::GraphicsManager::draw(Game* game, WaveManager* waveManager)
{
	if (drawSwitcher == 0)
	{
		// draw game scene
		drawPicture(game);
		interface->draw(game, waveManager);
	}
	else if (drawSwitcher == 1)
	{
		// draw minimap
		minimap->draw(game);
	}
	else if (drawSwitcher == 2)
	{
		craftingTable->draw(game);
	}

	game->window->display();
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
	int playerCellX = int(playerGlobalPositionX) / SQUARE_SIZE_PIXIL;
	int playerCellY = int(playerGlobalPositionY) / SQUARE_SIZE_PIXIL;

	// calculate borders of drawing rectangle
	int Left = max(0, playerCellX - 15);
	int Right = min(FIELD_SIZE - 1, playerCellX + 15);
	int Up = max(0, playerCellY - 10);
	int Down = min(FIELD_SIZE - 1, playerCellY + 10);

	//vector < vector < pair < double, double > > > drawingOrder;
	vector<pair<double, double> > groundsToDraw;
	vector <int> storagesToDraw;
	vector<pair<double, double> > craftingTablesToDraw;
	vector<pair<double, double> > bulletsToDraw;
	vector<pair<double, double> > enemiesToDraw;
	vector<pair<double, double> > treesToDraw;
	vector<pair<double, double> > grenadesToDraw;

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
			if (game->environment->field[i][j] == 5)
			{
				// add to the order
				treesToDraw.push_back({ playerPositionX + deltX, playerPositionY + deltY });
			}
			else if (game->environment->field[i][j] == 4)
			{
				craftingTablesToDraw.push_back({ playerPositionX + deltX, playerPositionY + deltY });
			}

			if (game->environment->storageNumber[i][j] != -1)
			{
				storagesToDraw.push_back(game->environment->storageNumber[i][j]);
			}
		}
	}

	// for all Bullets
	for (int i = 0; i < int(game->Bullets.size()); i++)
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
	playerSprite->setRotation(float(angle * 180 / acos(-1)));

	if (game->playerObject.isDamaged > 0)
	{
		playerSprite->setColor(Color::Red);
	}

	// add enemys
	for (int i = 0; i < int(game->Enemys.size()); i++)
	{
		pair < double, double > position;

		// calculate position in window
		position.first = playerPositionX + game->Enemys[i].getPosition().first - playerGlobalPositionX;
		position.second = playerPositionY + game->Enemys[i].getPosition().second - playerGlobalPositionY;

		// add to order
		enemiesToDraw.push_back(position);
	}

	// add grenades 
	for (int i = 0; i < int(game->grenades.size()); i++)
	{
		pair < double, double > position;
		
		// calculate position in window
		position.first = playerPositionX + game->grenades[i].getPosition().first - playerGlobalPositionX;
		position.second = playerPositionY + game->grenades[i].getPosition().second - playerGlobalPositionY;

		// add to order
		grenadesToDraw.push_back(position);
	}


	// for each type of sprites

	// draw grounds
	for (int j = 0; j < int(groundsToDraw.size()); j++)
	{
		groundSprite.setPosition(float(groundsToDraw[j].first), float(groundsToDraw[j].second));
		game->window->draw(groundSprite);
	}

	// draw storages
	for (auto& storageI : storagesToDraw)
	{
		game->environment->storages[storageI]->draw(game->window, playerGlobalPositionX - playerPositionX, playerGlobalPositionY - playerPositionY,
			playerGlobalPositionX, playerGlobalPositionY, storageSprite[game->environment->storages[storageI]->isLootable()]);
	}

	// draw craftingTables
	for (int j = 0; j < int(craftingTablesToDraw.size()); j++)
	{
		craftingTableSprite.setPosition(float(craftingTablesToDraw[j].first), float(craftingTablesToDraw[j].second));
		game->window->draw(craftingTableSprite);
	}

	// draw bullets
	for (int j = 0; j < int(bulletsToDraw.size()); j++)
	{
		bulletSprite.setPosition(float(bulletsToDraw[j].first), float(bulletsToDraw[j].second));
		game->window->draw(bulletSprite);
	}

	// draw grenades
	for (int j = 0; j < int(grenadesToDraw.size()); j++)
	{
		int pictureNumber = game->grenades[j].getNumberOfPicture();
		
		if (pictureNumber > 3)
		{
			continue;
		}

		grenadeSprite[pictureNumber].setPosition(float(grenadesToDraw[j].first), float(grenadesToDraw[j].second));
		game->window->draw(grenadeSprite[pictureNumber]);
	}

	// draw player
	playerSprite->setPosition(float(game->playerObject.getPositionInWindow().first), float(game->playerObject.getPositionInWindow().second));
	game->window->draw(*playerSprite);

	// draw enemys
	for (int j = 0; j < int(enemiesToDraw.size()); j++)
	{
		enemySprite.setPosition(float(enemiesToDraw[j].first), float(enemiesToDraw[j].second));
		enemySprite.setRotation(float(game->Enemys[j].getAngleWatching() * 180 / acos(-1)));
		game->window->draw(enemySprite);
	}

	// draw trees
	for (int j = 0; j < int(treesToDraw.size()); j++)
	{
		treeSprite.setPosition(float(treesToDraw[j].first), float(treesToDraw[j].second));
		game->window->draw(treeSprite);
	}

	// set base color to player sprite
	playerSprite->setColor(Color::White);

	return;
}

void Game::GraphicsManager::safe(ofstream& out, int& safeOption, void(*updSafeOption)(int&, int))
{
	minimap->safe(out, safeOption, updSafeOption);

	return;
}

void Game::GraphicsManager::loadStorageFonts(Game* game)
{
	storageFont.loadFromFile(ROBO_REGULAR_2_FILE_PATH);
	for (auto& storage : game->environment->storages)
	{
		storage->setFont(storageFont);
	}
}