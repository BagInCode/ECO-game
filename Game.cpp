#include "Game.h"
#include "Constants.db"

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
	if (!loadSprites())
	{
		return 0;
	}

	// init weapon
	PlayerWeapon.create(5000, 100, 1, 5 * acos(-1) / 180, 1, 30, 2, 0, &Bullets);

	Weapon weapon;
	weapon.create(330, 330, 1, 3 * acos(-1) / 180, 1, 30, 0, 0, &Bullets);

	Enemy enemy;
	enemy.create(1000, 1000, weapon);

	Enemys.push_back(enemy);
	Enemys.push_back(enemy);
	Enemys.push_back(enemy);
	Enemys.push_back(enemy);
	Enemys.push_back(enemy);

	EnemysState.push_back(new RunState());
	EnemysState.push_back(new RunState());
	EnemysState.push_back(new RunState());
	EnemysState.push_back(new RunState());
	EnemysState.push_back(new RunState());
	
	// start with drawing game scene
	isMinimapDrawing = 0;

	// generate field
	fieldGeneration();

	return 1;
}

void Game::checkTime(RenderWindow & window)
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

		// if minimap drawing
		if (isMinimapDrawing)
		{
			// draw minimap
			drawMinimap(window);
		}
		else
		{
			// draw game scene
			drawPicture(window);
		}

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

void Game::drawPicture(RenderWindow & window)
{
	/*
	* function of drawing picture in game window
	*
	* @param window - game window
	*/

	// clear previous picture, set color of background black
	window.clear(Color::Black);

	// get position of player sprite inside game window
	double playerPositionX = playerObject.getPositionInWindow().first;
	double playerPositionY = playerObject.getPositionInWindow().second;

	// get position of player sprite on map
	double playerGlobalPositionX = playerObject.getPosition().first;
	double playerGlobalPositionY = playerObject.getPosition().second;

	// get position in array of cell, where player stay
	int playerCellX = playerGlobalPositionX / SQUARE_SIZE_PIXIL;
	int playerCellY = playerGlobalPositionY / SQUARE_SIZE_PIXIL;

	// calculate borders of drawing rectangle
	int Left = max(0, playerCellX - 15);
	int Right = min(FIELD_SIZE - 1, playerCellX + 15);
	int Up = max(0, playerCellY - 10);
	int Down = min(FIELD_SIZE - 1, playerCellY + 10);

	// drawingOrder[i] - position of all sprites EnviromentSprite[i] on screen
	vector < vector < pair < double, double > > > drawingOrder;

	// resize vector to count sprites
	drawingOrder.resize(EnviromentSprite.size());

	// draw ground
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
			drawingOrder[0].push_back({ playerPositionX + deltX, playerPositionY + deltY });

			// if there is sth in this square
			if (Field[i][j] > 0)
			{
				// add to the order
				drawingOrder[Field[i][j]].push_back({ playerPositionX + deltX, playerPositionY + deltY });
			}
		}
	}

	// for all Bullets
	for (int i = 0; i < Bullets.size(); i++)
	{
		// get Bullet position
		double bulletPositionX = Bullets[i].getPosition().first;
		double bulletPositionY = Bullets[i].getPosition().second;

		// get difference
		double deltX = bulletPositionX - playerGlobalPositionX;
		double deltY = bulletPositionY - playerGlobalPositionY;

		// add to order
		drawingOrder[2].push_back({ playerPositionX + deltX, playerPositionY + deltY });
	}

	// add player to order
	drawingOrder[3].push_back(playerObject.getPositionInWindow());

	// get angle of player sprite
	double angle = playerObject.rotate(window);

	// set rotation, convert angle from radian to degree
	EnviromentSprite[3].setRotation(angle * 180 / acos(-1));

	// add enemys
	for (int i = 0; i < Enemys.size(); i++)
	{
		pair < double, double > position;

		// calculate position in window
		position.first = playerPositionX + Enemys[i].getPosition().first - playerGlobalPositionX;
		position.second = playerPositionY + Enemys[i].getPosition().second - playerGlobalPositionY;

		// add to order
		drawingOrder[4].push_back(position);
	}

	// for each type of sprites
	for (int i = 0; i < drawingOrder.size(); i++)
	{
		// for each position of this type of sprites
		for (int j = 0; j < drawingOrder[i].size(); j++)
		{
			// set position
			EnviromentSprite[i].setPosition(drawingOrder[i][j].first, drawingOrder[i][j].second);

			// if enemy sprite
			if (i == 4)
			{
				// set sprite rotation
				EnviromentSprite[i].setRotation(Enemys[j].getAngleWatching() * 180 / acos(-1));
			}

			// and draw
			window.draw(EnviromentSprite[i]);
		}
	}

	// set base color to player sprite
	EnviromentSprite[3].setColor(Color::White);

	// showing picture
	window.display();

	return;
}

void Game::switchEvent(Event event, RenderWindow& window)
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
		window.close();
	}

	// if window lost focus
	if (event.type == Event::LostFocus)
	{
		// set pause mod
		GamePausa gamePausa;

		if (!gamePausa.process(window))
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

			if (!gamePausa.process(window))
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
			isMinimapDrawing = !isMinimapDrawing;
		}

		// if key P
		if (event.key.code == Keyboard::P)
		{
			// use for debug, if you need to return to mainMenu
			gameOver = 1;
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

	return;
}

void Game::process(RenderWindow & window)
{
	/*
	* main function of game
	*
	* @param window - game window
	*/

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
			switchEvent(event, window);
		}

		// checking clock
		checkTime(window);

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

	// increase weapon timer
	PlayerWeapon.increaseTimer(timer);

	// action of shooting
	if (playerShooting)
	{
		PlayerWeapon.shoot(playerObject.getPosition(), playerObject.getAngle(), 0);
	}

	// update vision
	updateVision();

	// for all enemys
	for (int i = 0; i < Enemys.size(); i++)
	{
		// increase weapon timer
		Enemys[i].getWeaponPointer()->increaseTimer(timer);

		// do action
		EnemysState[i] -> doAction(timer, Enemys[i], playerObject);

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

	return;
}

void Game::fieldGeneration()
{
	/*
	* function of generating field
	*/

	/// make random more randomly
	srand(time(NULL));

	int x, y;

	// divid all fieald on squares 10x10 and random in each square independly
	for (int i = 0; i < FIELD_SIZE / 10; i++)
	{
		for (int j = 0; j < FIELD_SIZE / 10; j++)
		{
			// random position of house
			x = rand() % 7;
			y = rand() % 7;

			// set pointer of house in the top left corner of house
			Field[i * 10 + y][j * 10 + x] = 1;

			// in other square of house set pointer, that they are not empty
			Field[i * 10 + y + 1][j * 10 + x] = -1;
			Field[i * 10 + y + 2][j * 10 + x] = -1;
			Field[i * 10 + y][j * 10 + x + 1] = -1;
			Field[i * 10 + y + 1][j * 10 + x + 1] = -1;
			Field[i * 10 + y + 2][j * 10 + x + 1] = -1;

			// add to objects list (x1, x2, y1, y2, x1 < x2, y1 < y2)
			positionOfObjects.push_back({ { (j * 10 + x) * SQUARE_SIZE_PIXIL, (j * 10 + x + 2) * SQUARE_SIZE_PIXIL },
			{ (i * 10 + y) * SQUARE_SIZE_PIXIL, (i * 10 + y + 3) * SQUARE_SIZE_PIXIL } });

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
						Field[i * 10 + x][j * 10 + y] = EnviromentSprite.size()-1;

						//stop generating
						break;
					}
				}
			}
		}
	}

	return;
}

bool Game::loadSprites()
{
	/*
	* function of loading sprites
	*
	* @return true - if loadding complited
	*         false - if loading failed
	*/

	Sprite temp;

	// if texture does not load 
	if (!EnviromentTexture.loadFromFile("Textures\\Enviroment.png"))
	{
		// loadging failed
		return 0;
	}

	// set texture
	temp.setTexture(EnviromentTexture);

	// choose image rectangle of ground
	temp.setTextureRect(IntRect(0, 0, SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL));

	// add sprite
	EnviromentSprite.push_back(temp);

	// choose image rectangle of home
	temp.setTextureRect(IntRect(HAUSE_SPRITE_POSITION_LEFT, HAUSE_SPRITE_POSITION_TOP, HAUSE_SPRITE_LENGTH, HAUSE_SPRITE_HIGH));

	// add sprite
	EnviromentSprite.push_back(temp);

	// choose image rectangle of bullet
	temp.setTextureRect(IntRect(0, 0, 3, 3));

	// set color of sprite as red
	temp.setColor(Color::Red);

	// add sprite
	EnviromentSprite.push_back(temp);

	// set basic color
	temp.setColor(Color::White);

	// choose image rectangle of player
	temp.setTextureRect(IntRect(PLAYER_SPRITE_AK_POSITION_LEFT, PLAYER_SPRITE_AK_POSITION_TOP, PLAYER_SPRITE_AK_LENGTH, PLAYER_SPRITE_AK_HIGH));

	// set origin
	temp.setOrigin(PLAYER_SPRITE_AK_LENGTH / 2., PLAYER_SPRITE_AK_HIGH / 2.);

	// add sprite
	EnviromentSprite.push_back(temp);

	// set origin
	temp.setOrigin(ENEMY_SPRITE_LENGTH / 2., ENEMY_SPRITE_HIGH / 2.);

	// choose image rectangle of enemy
	temp.setTextureRect(IntRect(ENEMY_SPRITE_LEFT, ENEMY_SPRITE_TOP, ENEMY_SPRITE_LENGTH, ENEMY_SPRITE_HIGH));

	// add sprite
	EnviromentSprite.push_back(temp);

	// set basic origin
	temp.setOrigin(0, 0);

	// choose image rectangle of tree
	temp.setTextureRect(IntRect(TREE_SPRITE_POSITION_LEFT, TREE_SPRITE_POSITION_TOP, SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL));

	// add sprite
	EnviromentSprite.push_back(temp);

	// if texture does not load
	if (!MinimapTexture.loadFromFile("Textures\\Minimap.png"))
	{
		// loading failed
		return 0;
	}

	// set texture
	temp.setTexture(MinimapTexture);

	// set image rectangle of active ground
	temp.setTextureRect(IntRect(MINIMAP_GROUND_ACTIVE_SPRITE_LEFT, MINIMAP_GROUND_ACTIVE_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// add sprite
	MinimapSprite.push_back(temp);

	// set image rectangle of active house
	temp.setTextureRect(IntRect(MINIMAP_HOUSE_ACTIVE_SPRITE_LEFT, MINIMAP_HOUSE_ACTIVE_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// add sprite
	MinimapSprite.push_back(temp);

	// set image rectangle of active tree
	temp.setTextureRect(IntRect(MINIMAP_TREE_ACTIVE_SPRITE_LEFT, MINIMAP_TREE_ACTIVE_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// add sprite
	MinimapSprite.push_back(temp);

	// set image rectangle of player
	temp.setTextureRect(IntRect(MINIMAP_PLAYER_SPRITE_LEFT, MINIMAP_PLAYER_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// add sprite
	MinimapSprite.push_back(temp);

	// set image rectangle of enemy
	temp.setTextureRect(IntRect(MINIMAP_ENEMY_SPRITE_LEFT, MINIMAP_ENEMY_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// add sprite
	MinimapSprite.push_back(temp);

	// set image rectangle of invisible
	temp.setTextureRect(IntRect(MINIMAP_INVISIBLE_SPRITE_LEFT, MINIMAP_INVISIBLE_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// add sprite
	MinimapSprite.push_back(temp);

	// set image rectangle of inactive ground
	temp.setTextureRect(IntRect(MINIMAP_GROUND_INACTIVE_SPRITE_LEFT, MINIMAP_GROUND_INACTIVE_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// add sprite
	MinimapSprite.push_back(temp);

	// set image rectangle of inactive house
	temp.setTextureRect(IntRect(MINIMAP_HOUSE_INACTIVE_SPRITE_LEFT, MINIMAP_HOUSE_INACTIVE_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// add sprite
	MinimapSprite.push_back(temp);

	// set image rectangle of inactive tree
	temp.setTextureRect(IntRect(MINIMAP_TREE_INACTIVE_SPRITE_LEFT, MINIMAP_TREE_INACTIVE_SPRITE_TOP, MINIMAP_SQUARE_SIZE_PIXIL, MINIMAP_SQUARE_SIZE_PIXIL));

	// add sprite
	MinimapSprite.push_back(temp);

	return 1;
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
	for (int i = positionOfObjects.size()-1; i >= 0; i--)
	{
		// get coordinats of intersection
		double x1 = max(playerX1, positionOfObjects[i].first.first);
		double x2 = min(playerX2, positionOfObjects[i].first.second);

		double y1 = max(playerY1, positionOfObjects[i].second.first);
		double y2 = min(playerY2, positionOfObjects[i].second.second);

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
	for (int i = 0; i < positionOfObjects.size(); i++)
	{
		// get coordinats of intersection
		double x1 = max(enemyX1, positionOfObjects[i].first.first);
		double x2 = min(enemyX2, positionOfObjects[i].first.second);

		double y1 = max(enemyY1, positionOfObjects[i].second.first);
		double y2 = min(enemyY2, positionOfObjects[i].second.second);

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
		for (int j = 0; j < positionOfObjects.size(); j++)
		{
			// if intersection with houses
			if (positionOfObjects[j].first.first < currentPosition.first &&
				positionOfObjects[j].first.second > currentPosition.first &&
				positionOfObjects[j].second.first < currentPosition.second &&
				positionOfObjects[j].second.second > currentPosition.second)
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

				EnviromentSprite[3].setColor(Color::Red);

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

int Game::getManhetenDist(int x1, int y1, int x2, int y2)
{
	/*
	* function of getting manheten dist between two field squares
	*
	* @param x1, y1 - coordinate of first square
	*        x2, y2 - coordinate of second square
	*
	* @return manheten dist
	*/

	return abs(x1 - x2) + abs(y1 - y2);
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

void Game::drawMinimap(RenderWindow & window)
{
	/*
	* function of drawing minimap
	*
	* @param window - game window
	*/

	// clear window, set color of background black
	window.clear(Color::Black);

	// create pointer of sprite
	int pointerSprite = 0;

	// get position of player square
	int playerX = playerObject.getPosition().first / SQUARE_SIZE_PIXIL;
	int playerY = playerObject.getPosition().second / SQUARE_SIZE_PIXIL;

	// for all square
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			// if not opened square
			if (!visionMap[i][j])
			{
				// set pointer to invisible sprite
				pointerSprite = 5;
			}
			else
			{
				// if ground -> set pointer to the ground
				if (Field[i][j] == 0) pointerSprite = 0;

				// if house -> set pointer to the house
				if (abs(Field[i][j]) == 1) pointerSprite = 1;

				// if tree -> set pointer to the tree
				if (Field[i][j] == EnviromentSprite.size()-1) pointerSprite = 2;

				// if invisible -> move pointer to invisible pictures
				if (!isVisible(playerX, playerY, j, i))
				{
					pointerSprite += 6;
				}
			}

			// set position
			MinimapSprite[pointerSprite].setPosition(MINIMAP_DELT_X + j * MINIMAP_SQUARE_SIZE_PIXIL, i * MINIMAP_SQUARE_SIZE_PIXIL);

			// draw
			window.draw(MinimapSprite[pointerSprite]);
		}
	}

	// fro all enemys
	for (int i = 0; i < Enemys.size(); i++)
	{
		// get cordinates of square
		int enemyX = Enemys[i].getPosition().first / SQUARE_SIZE_PIXIL;
		int enemyY = Enemys[i].getPosition().second / SQUARE_SIZE_PIXIL;

		// if square is not visible
		if (!isVisible(playerX, playerY, enemyX, enemyY))
		{
			// go to next enemy
			continue;
		}

		// set position
		MinimapSprite[4].setPosition(MINIMAP_DELT_X + enemyX * MINIMAP_SQUARE_SIZE_PIXIL, enemyY * MINIMAP_SQUARE_SIZE_PIXIL);

		// draw
		window.draw(MinimapSprite[4]);
	}

	// set player sprite position
	MinimapSprite[3].setPosition(MINIMAP_DELT_X + playerX * MINIMAP_SQUARE_SIZE_PIXIL, playerY * MINIMAP_SQUARE_SIZE_PIXIL);

	// draw
	window.draw(MinimapSprite[3]);

	// sho picture
	window.display();

	return;
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

	// if next run state
	if (next == 0)
	{
		// return new run state
		return new RunState();
	}

	// if next stay state
	if (next == 1)
	{
		// return new stay state
		return new StayState();
	}

	// if next shoot state
	if (next == 2)
	{
		// return new shoo state
		return new ShootState();
	}

	// if next run on random vector state
	if (next == 3)
	{
		return new RunRandomVectorState();
	}
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