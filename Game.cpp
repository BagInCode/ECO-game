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

	gameOver = 0;

	// init player
	playerObject.create();

	// load enviroment sprites
	if (!loadSprites())
	{
		return 0;
	}

	// init weapon
	PlayerWeapon.create(5000, 100, 1, 5*acos(-1)/180, 1, 30, 0, 0);

	// start without pause
	pause = 0;

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

	// if game on pause
	if (pause)
	{
		// do not do any actions
		return;
	}

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
		// remember here last element to erase
		vector < vector < Bullet > :: iterator > eraseIt;

		// will be true if there are some bullets for deleting
		bool needToErase = 0;

		// move bullets
		for (vector < Bullet > ::iterator it = Bullets.begin(); it != Bullets.end(); it++)
		{
			// move it
			it->move(timer); 

			// it it is time to delete bullet
			if (it->readyToDelete())
			{
				// remember element for delete
				eraseIt.push_back(it);

				// set variable
				needToErase = 1;
			}
		}

		// if there are some bullets for deleting
		if (needToErase)
		{
			// for each element for deleting
			for (int i = 0; i < eraseIt.size(); i++)
			{
				// delete it
				Bullets.erase(eraseIt[i]);
			}
		}
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
	int Right = min(FIELD_SIZE-1, playerCellX + 15);
	int Up = max(0, playerCellY - 10);
	int Down = min(FIELD_SIZE-1, playerCellY + 10);

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
		drawingOrder[2].push_back({playerPositionX + deltX, playerPositionY + deltY});
	}

	// add player to order
	drawingOrder[3].push_back(playerObject.getPositionInWindow());

	// prepare to drawing
	prepareToDrawing(window);

	// for each type of sprites
	for (int i = 0; i < drawingOrder.size(); i++)
	{
		// for each position of this type of sprites
		for (int j = 0; j < drawingOrder[i].size(); j++)
		{
			// set position
			EnviromentSprite[i].setPosition(drawingOrder[i][j].first, drawingOrder[i][j].second);

			// and draw
			window.draw(EnviromentSprite[i]);
		}
	}

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
		makePause(1);
	}

	// if event of keypressing
	if (event.type == Event::KeyPressed)
	{
		// if key ESC
		if (event.key.code == Keyboard::Escape)
		{
			// set pause mod
			makePause();
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

void Game::makePause(int value)
{
	/*
	* function of setting/unsetting pause
	* -1 for switch (default)
	* 0 for unpause
	* 1 for pause
	*/

	// set pause value
	_ASSERT(value >= -1 && value <= 1);
	if (value == -1)
	{
		pause = !pause;
	}
	else if (value == 0)
	{
		pause = false;
	}
	else if (value == 1)
	{
		pause = true;
	}

	// restart clock
	myClock.restart();

	// stop player mooving
	playerObject.setMoovingVector(0, 0);

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
		PlayerWeapon.shoot(playerObject, Bullets);
	}

	// update vision
	updateVision();

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
			positionOfObjects.push_back({ {(j * 10 + x) * SQUARE_SIZE_PIXIL, (j * 10 + x + 2) * SQUARE_SIZE_PIXIL}, 
										  {(i * 10 + y) * SQUARE_SIZE_PIXIL, (i * 10 + y + 3) * SQUARE_SIZE_PIXIL} });

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
						Field[i * 10 + x][j * 10 + y] = 4;

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

void Game::prepareToDrawing(RenderWindow & window)
{
	/*
	* function of preparing to drawing (rotate, set scale, ect.)
	*
	* @param window - game window
	*/

	// get angle of player sprite
	double angle = playerObject.rotate(window);

	// set rotation, convert angle from radian to degree
	EnviromentSprite[3].setRotation(angle * 180 / acos(-1));

	return;
}

void Game::checkIntersection()
{
	/*
	* function of checking intersection of player and enemys with houses
	*/

	double playerSize = max(playerObject.getSize().first, playerObject.getSize().second);

	// get coordinats of corners of player sprite
	double playerX1 = playerObject.getPosition().first - playerSize / 2;
	double playerX2 = playerObject.getPosition().first + playerSize / 2;

	double playerY1 = playerObject.getPosition().second - playerSize / 2;
	double playerY2 = playerObject.getPosition().second + playerSize / 2;

	// for all objects
	for (int i = 0; i < positionOfObjects.size(); i++)
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
			}else
			{
				playerObject.setPosition(x2 + playerSize / 2., playerObject.getPosition().second);
			}
		}else
		{
			// if left
			if (flag2)
			{
				playerObject.setPosition(x1 - playerSize / 2., playerObject.getPosition().second);
			}else
			{
				playerObject.setPosition(playerObject.getPosition().first, y1 - playerSize / 2.);
			}
		}
	}

	return;
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
				if (Field[i][j] == 4) pointerSprite = 2;

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
	int Up = min(FIELD_SIZE-1, playerY + MAX_VISIBLE_DIST);
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