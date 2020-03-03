#include "Constants.db"
#include "Game.h"
#include "GameGraphicsManager.h"
#include "GameGraphicsManagerInterface.h"
#include "WaveManager.h"

Game::Game()
{
	graphics = new GraphicsManager;
	waves = new WaveManager;
}

Game::~Game()
{
	delete graphics;
	delete waves;
}

bool Game::initComponents()
{
	/*
	* function of initialization of components
	*
	* @return true - initialization completed
	*         false - initialization failed
	*/

	// game is not over
	gameOver = 0;

	// init player
	playerObject.create();

	// load enviroment sprites
	graphics->initComponents();

	// init weapon pistol
	allPlayerWeapon[0].create(3000, 300, 0.7, 3 * acos(-1) / 180, 1, 10, 5, &Bullets);

	// init weapon hunter double
	allPlayerWeapon[1].create(4000, 1000, 0.5, 10 * acos(-1) / 180, 5, 2, 4, &Bullets);

	// init weapon AK
	allPlayerWeapon[2].create(5000, 100, 1, 5 * acos(-1) / 180, 1, 30, 10, &Bullets);

	// init weapon minigan
	allPlayerWeapon[3].create(10000, 60, 1, 7.5 * acos(-1) / 180, 1, 100, 10, &Bullets);

	// init weapon sniper
	allPlayerWeapon[4].create(5000, 1000, 1.5, 1.5 * acos(-1) / 180, 1, 5, 50, &Bullets);

	// start with pistol
	currentWeaponPointer = 0;

	Weapon weapon;
	weapon.create(330, 330, 1, 3 * acos(-1) / 180, 1, 30, 0, &Bullets);

	Enemy enemy;

	enemy.create(1000, 1000, weapon);
	Enemys.push_back(enemy);
	enemy.create(1050, 1050, weapon);
	Enemys.push_back(enemy);
	enemy.create(1000, 1050, weapon);
	Enemys.push_back(enemy);
	enemy.create(1050, 1000, weapon);
	Enemys.push_back(enemy);
	enemy.create(1025, 1025, weapon);
	Enemys.push_back(enemy);

	EnemysState.push_back(new OutOfVisibilityState());
	EnemysState.push_back(new OutOfVisibilityState());
	EnemysState.push_back(new OutOfVisibilityState());
	EnemysState.push_back(new OutOfVisibilityState());
	EnemysState.push_back(new OutOfVisibilityState());

	// start with drawing game scene
	graphics->isMinimapDrawing = 0;

	// generate field
	fieldGeneration();

	return 1;
}

void Game::checkTime()
{
	/*
	* function of checking timer
	*
	* @param window - game window
	*/

	// get time delt
	double timerDelt = myClock.getElapsedTime().asMicroseconds() / 1000.;

	// restart clock
	myClock.restart();

	// increase timer
	timer += timerDelt;

	// if there is enough time passed
	if (timer > TIME_FOR_ACTION)
	{
		waves->checkTimer(timer, this);

		// do some actions
		doActions();

		// move objects
		moveObjects();

		// check intersections
		checkIntersection();

		// check game for ending
		checkGameOver();

		// check enemy
		checkEnemyAlive();

		// draw
		graphics->draw(this);

		// null timer
		timer = 0;
	}

	return;
}

void Game::moveObjects()
{
	/*
	* function of moving objects
	*/

	// move player
	playerObject.move(timer);

	// if there are some bullets 
	if (Bullets.size() > 0)
	{
		// create new vector
		vector < Bullet > newBullets;

		for (int i = 0; i < Bullets.size(); i++)
		{
			// move bullet
			Bullets[i].move(timer);

			// if bullet have to stay alife
			if (!Bullets[i].readyToDelete() && !checkIntersectionBullet(Bullets[i]))
			{
				// add to new vector
				newBullets.push_back(Bullets[i]);
			}
		}

		// overwrite old vector
		Bullets = newBullets;
	}

	return;
}

void Game::switchEvent(Event event)
{
	/*
	* function of switching event type and chosing reaction for it
	*
	* @param event - event
	*        window - game window
	*/

	// if event of closing window
	if (event.type == Event::Closed)
	{
		// close it
		window->close();
	}

	// if window lost focus
	if (event.type == Event::LostFocus)
	{
		// set pause mod
		GamePausa gamePausa;

		if (!gamePausa.process(*window))
		{
			gameOver = 1;
		}

		playerObject.setMoovingVector(0, 0);
		playerShooting = 0;
		timer = 0;
		myClock.restart();
	}

	// if event of keypressing
	if (event.type == Event::KeyPressed)
	{
		// if key ESC
		if (event.key.code == Keyboard::Escape)
		{
			// set pause mod
			GamePausa gamePausa;

			if (!gamePausa.process(*window))
			{
				gameOver = 1;
			}

			playerObject.setMoovingVector(0, 0);
			playerShooting = 0;
			timer = 0;
			myClock.restart();
		}

		// if key A
		if (event.key.code == Keyboard::A)
		{
			// set new speed vector, value 2 is out of possibility range, so Y-vector will be unchanged
			playerObject.setMoovingVector(-1, 2);
		}

		// if key S
		if (event.key.code == Keyboard::S)
		{
			// set new speed vector, value 2 is out of possibility range, so X-vector will be unchanged
			playerObject.setMoovingVector(2, 1);
		}

		// if key W
		if (event.key.code == Keyboard::W)
		{
			// set new speed vector, value 2 is out of possibility range, so X-vector will be unchanged
			playerObject.setMoovingVector(2, -1);
		}

		// if key D
		if (event.key.code == Keyboard::D)
		{
			// set new speed vector, value 2 is out of possibility range, so Y-vector will be unchanged
			playerObject.setMoovingVector(1, 2);
		}

		// if key M
		if (event.key.code == Keyboard::M)
		{
			// drowing minimap/drawing game scene
			graphics->isMinimapDrawing = !(graphics->isMinimapDrawing);
		}

		// if key 1
		if (event.key.code == Keyboard::Num1)
		{
			// update pointer
			currentWeaponPointer = 0;
			graphics->playerSprite = &graphics->playerPistolSprite;

			// set sprite size
			playerObject.setSize(PLAYER_SPRITE_AK_LENGTH, PLAYER_SPRITE_AK_HIGH);
		}

		// if key 2
		if (event.key.code == Keyboard::Num2)
		{
			// update pointer
			currentWeaponPointer = 1;
			graphics->playerSprite = &graphics->playerShotgunSprite;

			// set sprite size
			playerObject.setSize(PLAYER_SPRITE_AK_LENGTH, PLAYER_SPRITE_AK_HIGH);
		}

		// if key 3
		if (event.key.code == Keyboard::Num3)
		{
			// update pointer
			currentWeaponPointer = 2;
			graphics->playerSprite = &graphics->playerRifleSprite;

			// set sprite size
			playerObject.setSize(PLAYER_SPRITE_AK_LENGTH, PLAYER_SPRITE_AK_HIGH);
		}

		// if key 4
		if (event.key.code == Keyboard::Num4)
		{
			// update pointer
			currentWeaponPointer = 3;

			// set sprite
			graphics->playerSprite = &graphics->playerMachinGunSprite;

			// set sprite size
			playerObject.setSize(PLAYER_SPRITE_AK_LENGTH, PLAYER_SPRITE_AK_HIGH);
		}

		// if key 5
		if (event.key.code == Keyboard::Num5)
		{
			// update pointer
			currentWeaponPointer = 4;

			// set sniper sprite
			graphics->playerSprite = &graphics->playerSniperRifleSprite;

			// set sprite size
			playerObject.setSize(PLAYER_SNIPER_LENGTH, PLAYER_SPRITE_AK_HIGH);
		}

		if (event.key.code == Keyboard::E)
		{
			double playerPositionX = playerObject.getPosition().first;
			double playerPositionY = playerObject.getPosition().second;

			for (int i = max(0, int(playerPositionY / SQUARE_SIZE_PIXIL - 5)); i <= min(99, int(playerPositionY / SQUARE_SIZE_PIXIL + 5)); i++)
			{
				for (int j = max(0, int(playerPositionX / SQUARE_SIZE_PIXIL - 5)); j <= min(99, int(playerPositionX / SQUARE_SIZE_PIXIL + 5)); j++)
				{
					if (storageNumber[i][j] != -1)
					{
						if (storages[storageNumber[i][j]].isLootable(playerPositionX, playerPositionY))
						{
							graphics->interface->addAction("Loot storage", 5.0);

							pair<int, int> lootResult = storages[storageNumber[i][j]].tryToLoot(playerPositionX, playerPositionY);

							// todo smth with lootresult
						}
					}
				}
			}
		}

		// if reload button pressed
		if (event.key.code == Keyboard::R)
		{
			// start reload
			allPlayerWeapon[currentWeaponPointer].startReload();
		}
	}

	if (event.type == Event::KeyReleased)
	{
		// if key A
		if (event.key.code == Keyboard::A)
		{
			// set new speed vector, value 2 is out of possibility range, so Y-vector will be unchanged
			playerObject.setMoovingVector(0, 2);
		}

		// if key S
		if (event.key.code == Keyboard::S)
		{
			// set new speed vector, value 2 is out of possibility range, so X-vector will be unchanged
			playerObject.setMoovingVector(2, 0);
		}

		// if key W
		if (event.key.code == Keyboard::W)
		{
			// set new speed vector, value 2 is out of possibility range, so X-vector will be unchanged
			playerObject.setMoovingVector(2, 0);
		}

		// if key D
		if (event.key.code == Keyboard::D)
		{
			// set new speed vector, value 2 is out of possibility range, so Y-vector will be unchanged
			playerObject.setMoovingVector(0, 2);
		}
	}

	// if mouse button pressed
	if (event.type == Event::MouseButtonPressed)
	{
		// if LMB
		if (event.mouseButton.button == Mouse::Left)
		{
			playerShooting = 1;
		}
	}

	// if mouse button released
	if (event.type == Event::MouseButtonReleased)
	{
		// if LMB
		if (event.mouseButton.button == Mouse::Left)
		{
			playerShooting = 0;
		}
	}

	// if wheel scrolled
	if (event.type == Event::MouseWheelScrolled)
	{
		if (event.mouseWheelScroll.delta > 0)
		{
			// get next weapon
			currentWeaponPointer = (currentWeaponPointer + 1) % 5;
		}
		else if (event.mouseWheelScroll.delta < 0)
		{
			// get previous weapon
			currentWeaponPointer = (currentWeaponPointer + 4) % 5;
		}

		// set sprite
		switch (currentWeaponPointer)
		{
		case 0: graphics->playerSprite = &graphics->playerPistolSprite; break;
		case 1: graphics->playerSprite = &graphics->playerShotgunSprite; break;
		case 2: graphics->playerSprite = &graphics->playerRifleSprite; break;
		case 3: graphics->playerSprite = &graphics->playerMachinGunSprite; break;
		case 4: graphics->playerSprite = &graphics->playerSniperRifleSprite; break;
		}

		if (currentWeaponPointer == 4)
		{
			// set sprite size
			playerObject.setSize(PLAYER_SNIPER_LENGTH, PLAYER_SPRITE_AK_HIGH);
		}
		else
		{
			// set sprite size
			playerObject.setSize(PLAYER_SPRITE_AK_LENGTH, PLAYER_SPRITE_AK_HIGH);
		}
	}

	return;
}

void Game::process(RenderWindow & window)
{
	/*
	* main function of game
	*
	* @param window - game window
	*/

	this->window = &window;

	// init game components
	initComponents();

	// starting clock counter
	myClock.restart();

	// while game is not closed
	while (window.isOpen() && !gameOver)
	{
		// if there is some event
		if (window.pollEvent(event))
		{
			// make some reaction
			switchEvent(event);
		}

		// checking clock
		checkTime();

		// if game over
		if (gameOver != 0)
		{
			break;
		}
	}

	return;
}

void Game::doActions()
{
	/*
	* function of doing some actions
	*/
	graphics->update(timer);

	// increase weapon timer
	allPlayerWeapon[currentWeaponPointer].increaseTimer(timer);

	// action of shooting
	if (playerShooting)
	{
		allPlayerWeapon[currentWeaponPointer].shoot(playerObject.getPosition(), playerObject.getAngle(), 0);
	}

	// update vision
	updateVision();

	// for all enemys
	for (int i = 0; i < Enemys.size(); i++)
	{
		// increase weapon timer
		Enemys[i].getWeaponPointer()->increaseTimer(timer);

		// do action
		EnemysState[i]->doAction(timer, Enemys[i], playerObject);

		// try next state
		int next = EnemysState[i]->goNext(Enemys[i], playerObject);

		// if there is some
		if (next != -1)
		{
			// delete previous
			delete EnemysState[i];

			// overwrite
			EnemysState[i] = chooseNext(next);
		}

		// calculate coordinates of vector (enemy position -> player position)
		double deltX = playerObject.getPosition().first - Enemys[i].getPosition().first;
		double deltY = playerObject.getPosition().second - Enemys[i].getPosition().second;

		// get angle between this vector and vector (0 1)
		double angle = atan2(deltY, deltX);

		// set angle to player position
		Enemys[i].setAngleWatching(angle);
	}

	for (auto& storage : storages)
	{
		storage.update(timer);
	}

	playerObject.isDamaged = max(playerObject.isDamaged - 1, 0);

	return;
}

void Game::fieldGeneration()
{
	/*
	* function of generating field
	*/

	/// make random more randomly
	srand(time(NULL));

	for (auto& row : Field)
	{
		for (auto& cell : row)
		{
			cell = 0;
		}
	}

	for (auto& row : storageNumber)
	{
		for (auto& cell : row)
		{
			cell = -1;
		}
	}

	int x, y;

	storageFont.loadFromFile(ROBO_REGULAR_2_FILE_PATH);
	int storageIndex = 0;
	// divid all fieald on squares 10x10 and random in each square independly
	for (int i = 0; i < FIELD_SIZE / 10; i++)
	{
		for (int j = 0; j < FIELD_SIZE / 10; j++)
		{
			// random position of house
			x = rand() % 7;
			y = rand() % 7;

			storageNumber[i * 10 + y][j * 10 + x] = storageIndex;
			storageIndex++;
			storages.push_back(Storage((j * 10 + x) * SQUARE_SIZE_PIXIL, (j * 10 + x + 2) * SQUARE_SIZE_PIXIL,
				(i * 10 + y) * SQUARE_SIZE_PIXIL, (i * 10 + y + 3) * SQUARE_SIZE_PIXIL, storageFont));

			// in other square of house set pointer, that they are not empty
			Field[i * 10 + y][j * 10 + x] = -1;
			Field[i * 10 + y + 1][j * 10 + x] = -1;
			Field[i * 10 + y + 2][j * 10 + x] = -1;
			Field[i * 10 + y][j * 10 + x + 1] = -1;
			Field[i * 10 + y + 1][j * 10 + x + 1] = -1;
			Field[i * 10 + y + 2][j * 10 + x + 1] = -1;


			// generate tree
			for (int k = 0; k < COUNT_TREES_IN_SQUARE; k++)
			{
				// generete while not get empty square
				while (1)
				{
					// random position
					x = rand() % 10;
					y = rand() % 10;

					// if square is empty
					if (Field[i * 10 + x][j * 10 + y] == 0)
					{
						// set tree in this square
						Field[i * 10 + x][j * 10 + y] = 5;

						//stop generating
						break;
					}
				}
			}
		}
	}

	return;
}

void Game::checkIntersection()
{
	/*
	* function of checking intersection
	*/

	// check player
	checkIntersectionPlayer();

	// check all enemys
	for (int i = 0; i < Enemys.size(); i++)
	{
		checkIntersectionEnemy(Enemys[i]);
	}

	return;
}

void Game::checkIntersectionPlayer()
{
	/*
	* function of checking intersection of player with houses
	*/

	double playerSize = max(playerObject.getSize().first, playerObject.getSize().second);

	// get coordinats of corners of player sprite
	double playerX1 = playerObject.getPosition().first - playerSize / 2;
	double playerX2 = playerObject.getPosition().first + playerSize / 2;

	double playerY1 = playerObject.getPosition().second - playerSize / 2;
	double playerY2 = playerObject.getPosition().second + playerSize / 2;

	// for all objects
	for (int i = 0; i < storages.size(); i++)
	{
		// get coordinats of intersection
		double x1 = max(playerX1, storages[i].x1);
		double x2 = min(playerX2, storages[i].x2);

		double y1 = max(playerY1, storages[i].y1);
		double y2 = min(playerY2, storages[i].y2);

		// if rectangle with negative square
		if (x1 > x2 || y1 > y2)
		{
			// go to the next object
			continue;
		}

		// get oriented area
		bool flag1 = orientedArea(playerObject.getPosition().first, playerObject.getPosition().second, x1, y2, x2, y1);
		bool flag2 = orientedArea(playerObject.getPosition().first, playerObject.getPosition().second, x1, y1, x2, y2);

		// if moving up or right
		if (flag1)
		{
			// if up
			if (flag2)
			{
				playerObject.setPosition(playerObject.getPosition().first, y2 + playerSize / 2.);
			}
			else
			{
				playerObject.setPosition(x2 + playerSize / 2., playerObject.getPosition().second);
			}
		}
		else
		{
			// if left
			if (flag2)
			{
				playerObject.setPosition(x1 - playerSize / 2., playerObject.getPosition().second);
			}
			else
			{
				playerObject.setPosition(playerObject.getPosition().first, y1 - playerSize / 2.);
			}
		}
	}

	return;
}

void Game::checkIntersectionEnemy(Enemy & enemy)
{
	/*
	* function of checking intersection of enemy with houses
	*/

	double enemySize = max(enemy.getSize().first, enemy.getSize().second);

	// get coordinats of corners of enemy sprite
	double enemyX1 = enemy.getPosition().first - enemySize / 2;
	double enemyX2 = enemy.getPosition().first + enemySize / 2;

	double enemyY1 = enemy.getPosition().second - enemySize / 2;
	double enemyY2 = enemy.getPosition().second + enemySize / 2;

	// for all objects
	for (int i = 0; i < storages.size(); i++)
	{
		// get coordinats of intersection
		double x1 = max(enemyX1, storages[i].x1);
		double x2 = min(enemyX2, storages[i].x2);

		double y1 = max(enemyY1, storages[i].y1);
		double y2 = min(enemyY2, storages[i].y2);

		// if rectangle with negative square
		if (x1 > x2 || y1 > y2)
		{
			// go to the next object
			continue;
		}

		// get oriented area
		bool flag1 = orientedArea(enemy.getPosition().first, enemy.getPosition().second, x1, y2, x2, y1);
		bool flag2 = orientedArea(enemy.getPosition().first, enemy.getPosition().second, x1, y1, x2, y2);

		// if moving up or right
		if (flag1)
		{
			// if up
			if (flag2)
			{
				enemy.setPosition(enemy.getPosition().first, y2 + enemySize / 2.);
			}
			else
			{
				enemy.setPosition(x2 + enemySize / 2., enemy.getPosition().second);
			}
		}
		else
		{
			// if left
			if (flag2)
			{
				enemy.setPosition(x1 - enemySize / 2., enemy.getPosition().second);
			}
			else
			{
				enemy.setPosition(enemy.getPosition().first, y1 - enemySize / 2.);
			}
		}
	}

	return;
}

bool Game::checkIntersectionBullet(Bullet & bullet)
{
	/*
	* function of checking intersection bullets with objects
	*
	* @param bullet - bulet
	*
	* @return true - if bullet have intersection with any object
	*/

	// calculate vector of bullet moving
	pair < double, double > vectorMoving = bullet.getPosition();

	vectorMoving.first -= bullet.getPreviousPosition().first;
	vectorMoving.second -= bullet.getPreviousPosition().second;

	// set position ofr checking
	pair < double, double > currentPosition = bullet.getPreviousPosition();

	// for all segments
	for (int i = 0; i <= COUNT_SEGMENTS_FOR_BULLET_CHECKING; i++)
	{
		// check intersection with houses
		for (int j = 0; j < storages.size(); j++)
		{
			// if intersection with houses
			if (storages[j].x1 < currentPosition.first && storages[j].x2 > currentPosition.first &&
				storages[j].y1 < currentPosition.second && storages[j].y2 > currentPosition.second)
			{
				return 1;
			}
		}

		// if target is player
		if (bullet.getIsPlayerTarget())
		{
			// calculate position of body rectangle
			double playerX1 = playerObject.getPosition().first - CHARACTER_BODY_RADIUS;
			double playerX2 = playerObject.getPosition().first + CHARACTER_BODY_RADIUS;
			double playerY1 = playerObject.getPosition().second - CHARACTER_BODY_RADIUS;
			double playerY2 = playerObject.getPosition().second + CHARACTER_BODY_RADIUS;

			// if there is intersection
			if (playerX1 < currentPosition.first &&
				playerX2 > currentPosition.first &&
				playerY1 < currentPosition.second &&
				playerY2 > currentPosition.second)
			{
				playerObject.getDamage(bullet.getDamage());
				graphics->interface->addAction("Get damage", 1.0);

				playerObject.isDamaged = 2;

				return 1;
			}
		}
		else
		{
			for (int j = 0; j < Enemys.size(); j++)
			{
				// calculate position of body rectangle
				double enemyX1 = Enemys[j].getPosition().first - CHARACTER_BODY_RADIUS;
				double enemyX2 = Enemys[j].getPosition().first + CHARACTER_BODY_RADIUS;
				double enemyY1 = Enemys[j].getPosition().second - CHARACTER_BODY_RADIUS;
				double enemyY2 = Enemys[j].getPosition().second + CHARACTER_BODY_RADIUS;

				// if there is intersection
				if (enemyX1 < currentPosition.first &&
					enemyX2 > currentPosition.first &&
					enemyY1 < currentPosition.second &&
					enemyY2 > currentPosition.second)
				{
					Enemys[j].getDamage(bullet.getDamage());

					return 1;
				}
			}
		}

		// go to next position
		currentPosition.first += vectorMoving.first / COUNT_SEGMENTS_FOR_BULLET_CHECKING;
		currentPosition.second += vectorMoving.second / COUNT_SEGMENTS_FOR_BULLET_CHECKING;
	}

	return 0;
}

bool Game::orientedArea(double x1, double y1, double x2, double y2, double x3, double y3)
{
	/*
	* function of getting oriented area of triangle A(x1, y1) B(x2,y2) C(x3, y3)
	*
	* @param x1, y1, x2, y2, x3, y3 - coordinates of triangle vertex
	* @return true if oriented area greather than zero
	*/

	// calculate area
	double S = x1*y2 + y1*x3 + x2*y3 - y2*x3 - x2*y1 - x1*y3;

	return (S > 0);
}

bool Game::isVisible(int playerX, int playerY, int x, int y)
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

void Game::updateVision()
{
	/*
	* function of updating minimap vision
	*/

	// get position of player square
	int playerX = playerObject.getPosition().first / SQUARE_SIZE_PIXIL;
	int playerY = playerObject.getPosition().second / SQUARE_SIZE_PIXIL;

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

	return;
}

void Game::checkGameOver()
{
	/*
	* function of checking game for ending
	*/

	// player die
	if (playerObject.getHealthPoints() < 1)
	{
		gameOver = -1;
	}

	// get player poisition
	double playerX = playerObject.getPosition().first;
	double playerY = playerObject.getPosition().second;

	for (int i = 0; i < Enemys.size(); i++)
	{
		// get enemy position
		double enemyX = Enemys[i].getPosition().first;
		double enemyY = Enemys[i].getPosition().second;

		// get dist between player and this enemy 
		double dist = sqrt((enemyX - playerX) * (enemyX - playerX) + (enemyY - playerY) * (enemyY - playerY));

		// if enemy too close
		if (dist < ENDING_RADIUS)
		{
			gameOver = -1;

			break;
		}
	}

	return;
}

State* Game::chooseNext(int next)
{
	/*
	* functionf of choosing next state
	*
	* @param next - integet pointer to next state
	*
	* @return pointer to new state
	*/

	State* result = nullptr;

	// if next run state
	if (next == 0)
	{
		// create new run state
		result = new RunState();

		// randomize result
		result->randomizeState();
	}

	// if next stay state
	if (next == 1)
	{
		// create new stay state
		result = new StayState();

		// randomize state
		result->randomizeState();
	}

	// if next shoot state
	if (next == 2)
	{
		// create new shoot state
		result = new ShootState();

		// randomize state
		result->randomizeState();
	}

	// if next run on random vector state
	if (next == 3)
	{
		// create new state
		result = new RunRandomVectorState();

		// randomize state
		result->randomizeState();
	}

	// if next out of visibility state
	if (next == 4)
	{
		// create new state
		result = new OutOfVisibilityState();
	}

	return result;
}

void Game::checkEnemyAlive()
{
	/*
	* function of checking is enemy alive or not
	*/

	// create new enemy vector
	vector < Enemy > newEnemys;

	// for all enemys
	for (int i = 0; i < Enemys.size(); i++)
	{
		// if enemy alive
		if (!Enemys[i].isDead())
		{
			// add to new vector
			newEnemys.push_back(Enemys[i]);
		}
	}

	// overwite previous vector
	Enemys = newEnemys;

	return;
}