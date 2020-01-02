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

	Sprite temp;

	// if texture does not load 
	if(!EnviromentTexture.loadFromFile("Textures\\Enviroment.png"))
	{
		// initialization failed
		return 0;
	}

	// set texture
	temp.setTexture(EnviromentTexture);

	// choose image rectangle of ground
	temp.setTextureRect(IntRect(0, 0, SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL));

	// add sprite
	EnviromentSprite.push_back(temp);

	// init player
	if (!playerObject.create())
	{
		return 0;
	}

	// init bullet sprite - red circle with radius 2
	bulletSprite.setFillColor(Color::Red);
	bulletSprite.setRadius(2);

	// init weapon
	PlayerWeapon.create(5000, 100, 1, 5*acos(-1)/180, 1, 30, 0, 0);

	// start without pause
	pause = 0;

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

		// draw picture
		drawPicture(window);

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
	int Left = max(0, playerCellX - 13);
	int Right = min(FIELD_SIZE, playerCellX + 13);
	int Up = max(0, playerCellY - 7);
	int Down = min(FIELD_SIZE, playerCellY + 7);

	// draw
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

			// set position for ground sprite
			EnviromentSprite[0].setPosition(playerPositionX + deltX, playerPositionY + deltY);

			// draw ground
			window.draw(EnviromentSprite[0]);
		}
	}
	
	// draw bullets
	for (vector < Bullet > ::iterator it = Bullets.begin(); it != Bullets.end(); it++)
	{
		// get bullet position on map
		pair < double, double > bulletPosition = it->getPosition();

		// bullet position inside game window
		pair < double, double > bulletPositionInWindow;

		// calculate bullet position inside game window
		bulletPositionInWindow.first = playerPositionX + bulletPosition.first - playerGlobalPositionX;
		bulletPositionInWindow.second = playerPositionY + bulletPosition.second - playerGlobalPositionY;

		// set position
		bulletSprite.setPosition(bulletPositionInWindow.first, bulletPositionInWindow.second);

		// draw
		window.draw(bulletSprite);
	}

	// draw player
	playerObject.draw(window);

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
		makePause();
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

void Game::makePause()
{
	/*
	* function of setting/unsetting pause
	*/

	// set pause value
	pause = !pause;

	// stop player mooving
	playerObject.setMoovingVector(0, 0);

	return;
}

void Game::process(RenderWindow & window)
{
	/*
	* main function of game
	*
	*/

	// init game components
	initComponents();

	// starting clock counter
	myClock.restart();

	// while game is not closed
	while (window.isOpen())
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

	return;
}