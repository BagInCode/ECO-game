#include "Game.h"



Game::Game()
{
}


Game::~Game()
{
}


bool Game::equal(Event lValue, Event rValue)
{
	/*
	* function of checking: are two Event object equal or not
	*
	* two Event object are equal if 
	*     both are event of key pressed/released and they have same key code;
	*     both are event of mouse button pressed/released and they have same mouse button code;
	* 
	* @param lValue - event made by user 
	*        rValue - system event for checking with
	*
	* @return true - events are equal
	*         false - events are different
	*/

	if ((lValue.type == Event::KeyPressed || lValue.type == Event::KeyReleased) && rValue.type == Event::KeyPressed)
	{
		return (lValue.key.code == rValue.key.code);
	}

	if ((lValue.type == Event::MouseButtonPressed || lValue.type == Event::MouseButtonReleased) && rValue.type == Event::MouseButtonPressed)
	{
		return (lValue.mouseButton.button == rValue.mouseButton.button);
	}

	return 0;
}

bool Game::loadSprites()
{	
	/*
	* function of loadind textures and sprites for map
	*
	* @return true - if loading completed
	*         false - if loading failed
	*/

	// if texture image do not load  
	if (!EnviromentTexture.loadFromFile("Textures\\Enviroment.png"))
	{
		// return false
		return 0;
	}

	// create ground sprite
	Sprite ground;
	ground.setTexture(EnviromentTexture);
	ground.setTextureRect(IntRect(GROUND_SPRITE_POSITION_X, GROUND_SPRITE_POSITION_Y, ENVIROMENT_SPRITE_LENGTH, ENVIROMENT_SPRITE_HIGH));

	// add ground sprite 
	enviroment.push_back(ground);

	// create tree sprite
	Sprite tree;
	tree.setTexture(EnviromentTexture);
	tree.setTextureRect(IntRect(TREE_SPRITE_POSITION_X, TREE_SPRITE_POSITION_Y, ENVIROMENT_SPRITE_LENGTH, ENVIROMENT_SPRITE_HIGH));

	// add tree sprite
	enviroment.push_back(tree);

	// creating road sprites
	
	Sprite _road;
	_road.setTexture(EnviromentTexture);

	// resize roads vector
	road.resize(16);

	/*
	* I (@BagInCode) will use bitmask for numerating roads
	*
	* For example:
	* 
	* let use next picture:
	*
	*  3     X - position of road sprite
	* 2X0
	*  1     0,1,2,3 - abstract numerating of neighbours
	*
	* if there is straight road from left to right, it conect neighbours with number 2 and 0
	* it is equal to next mask (1 - if connect, 0 - if not)
	*
	* 3 2 1 0 | neighbour number
	* 0 1 0 1 | connect or not
	*
	* let imagine, this is not a table, bat number in binary system
	* in decade system this number is equal to: 2^0 + 2^2 = 1 + 4 = 5
	* so remember this road in sprite with number 5
	*/

	// creating straight roads
	_road.setTextureRect(IntRect(ROAD_STRAIGHT_POSITION_X, 0, SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL)); // road from left to right
	road[5] = _road;

	_road.setTextureRect(IntRect(ROAD_STRAIGHT_POSITION_X, SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL)); // road from up to down
	road[10] = _road;

	// creating turn roads
	_road.setTextureRect(IntRect(ROAD_TURN_POSITION_X, 0, SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL)); // turn from down to right
	road[3] = _road;
	
	_road.setTextureRect(IntRect(ROAD_TURN_POSITION_X, SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL)); // turn from left to down
	road[6] = _road;

	_road.setTextureRect(IntRect(ROAD_TURN_POSITION_X, 2*SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL)); // turn from left to up
	road[12] = _road;

	_road.setTextureRect(IntRect(ROAD_TURN_POSITION_X, 3*SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL)); // turn from up to right
	road[9] = _road;
	
	//creating triple roads
	_road.setTextureRect(IntRect(ROAD_TRIPLE_POSITION_X, 0, SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL)); // road not to up
	road[7] = _road;

	_road.setTextureRect(IntRect(ROAD_TRIPLE_POSITION_X, SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL)); // road not to right
	road[14] = _road;

	_road.setTextureRect(IntRect(ROAD_TRIPLE_POSITION_X, 2*SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL)); // road not to down
	road[13] = _road;

	_road.setTextureRect(IntRect(ROAD_TRIPLE_POSITION_X, 3*SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL)); // road not to left
	road[11] = _road;

	// creating quadr road
	_road.setTextureRect(IntRect(ROAD_QUADR_POSITION_X, 0, SQUARE_SIZE_PIXIL, SQUARE_SIZE_PIXIL));
	road[15] = _road;

	// loading complete
	return 1;
}

bool Game::createPlayer(double newPositionX, double newPositionY, int healthPoints, int armorPoints)
{
	/*
	* function of initialization PlayerObject
	*
	* @param newPositionX, newPositionY - start position of player
	*        healthPoints - count health points
	*        armorPoints - count armor points
	*
	* @return true - if initialization completed
	*         false - if initialization failed
	*/

	// if initialization failed
	if (!PlayerObject.create(newPositionX, newPositionY, healthPoints, armorPoints))
	{
		// return false
		return 0;
	}

	// return true
	return 1;
}

bool Game::loadSave(double & newPositionX, double & newPositionY, int & healthPoints, int & armorPoints)
{
	/*
	* functiont of loading saved game
	* 
	* @param pointers to:
	*                    newPositionX, newPositionY - start player position
	*                    healthPoints - count player health points
	*                    armorPoints - count player armor points
	*
	* @return true - if loading completed
	*         false - if loading failed
	*/

	// create input file stream for readin from save file
	ifstream in;

	// open save file
	in.open("Saves\\saveFile.db");
	
	// if some trouble - load default values
	if (!in.is_open())
	{
		loadDefault(newPositionX, newPositionY, healthPoints, armorPoints);
	}
	
	// loading completed
	return 1;
}

void Game::loadDefault(double & newPositionX, double & newPositionY, int & healthPoints, int & armorPoints)
{
	/*
	* function of loading default control, weapon and players settings
	*
	* @param pointers to
	*                newPositionX, newPositionY - player position
	*                healthPoints - player health points
	*                armorPoints - armor points
	*/

	// default move up key - W
	MoveUp.key.code = Keyboard::W;
	MoveUp.type = Event::KeyPressed;

	// default move down key - S
	MoveDown.key.code = Keyboard::S;
	MoveDown.type = Event::KeyPressed;

	// default move left key - A
	MoveLeft.key.code = Keyboard::A;
	MoveLeft.type = Event::KeyPressed;

	// default move right key - D
	MoveRight.key.code = Keyboard::D;
	MoveRight.type = Event::KeyPressed;

	// default shoot button - LMB
	Shoot.mouseButton.button = Mouse::Left;
	Shoot.type = Event::MouseButtonPressed;

	// default player start position - centre of map
	newPositionX = (FIELD_LENGTH_PIXIL - PLAYER_SPRITE_LENGTH) / 2;
	newPositionY = (FIELD_HIGH_PIXIL - PLAYER_SPRITE_HIGH) / 2;

	// default health points - 100
	healthPoints = 100;

	// default armor points - 0
	armorPoints = 0;

	// create default weapons
	PlayerWeapons[0].create(0);

}

bool Game::loadGame()
{
	/*
	* function of loading game save and settings, creating sprites
	*
	* @return true - if loading completed
	*         false - if loading failed
	*/

	// creating player config values
	double newPositionX, newPositionY;
	int healthPoints, armorPoints;

	// load save
	if (!loadSave(newPositionX, newPositionY, healthPoints, armorPoints)) 
	{
		// save doesn`t load -> loading failed
		return 0;
	}

	// player config values loaded -> create Player object
	if (!createPlayer(newPositionX, newPositionY, healthPoints, armorPoints))
	{
		// Player object doesn`t create -> loading failed
		return 0;
	}
	
	// load map sprites
	if (!loadSprites())
	{
		// sprites doesn`t load -> loading failed
		return 0;
	}

	// generate map
	generateField();

	// loading comlete
	return 1;
}

bool Game::createEnemies()
{
	/*
	* function of creating Enemies
	*
	* @return true - if creating completed
	*         false - if creating failed
	*/

	// creating complete
	return 1;
}

void Game::generateField()
{
	/*
	* function of generating field
	*/

	// creating road

	// calc haw much turns will have road
	int countTurns = rand() % (FIELD_LENGTH / 10);

	cerr << countTurns << "\n";

	// position of new turn
	// generate start point
	int positionX = 0;
	int positionY = rand() % FIELD_HIGH;
	
	// position of previous turn
	int previousX;
	int previousY;

	// create turns
	for (int i = 0; i < countTurns; i++)
	{
		// remember previous position
		previousX = positionX;
		previousY = positionY;

		// if move left/right
		if (!(i & 1))
		{
			// generate end of moving
			positionX = rand() % (FIELD_LENGTH - 1);

			if (positionX >= previousX)
			{
				positionX++;
			}

			// set road
			for (int j = min(positionX, previousX); j <= max(positionX, previousX); j++)
			{
				Field[j][positionY] = 2;
			}
		}else // if move up/down
		{
			//generate end of moving
			positionY = rand() % (FIELD_HIGH - 1);

			if (positionY >= previousY)
			{
				positionY++;
			}

			// set road
			for (int j = min(positionY, previousY); j <= max(positionY, previousY); j++)
			{
				Field[positionX][j] = 2;
			}
		}
	}

	// set road to the end of map
	for (int i = positionX; i < FIELD_LENGTH; i++)
	{
		Field[i][positionY] = 2;
	}

	// creating trees
	for(int i = 0; i < COUNT_TREE; i++)
	{
		// set position
		int positionX = rand() % FIELD_LENGTH;
		int positionY = rand() % FIELD_HIGH;

		// if field square is not empty
		if (Field[positionX][positionY])
		{
			// redo
			i--;
		}else
		{
			// set tree to this square
			Field[positionX][positionY] = 1;
		}
	}

	return;
}

int Game::getRoadNumber(int positionX, int positionY)
{
	/*
	* function of getting road sprite number
	*
	* @param positionX, positionY - position field square (not on map)
	*
	* @return number of road sprite
	*/

	/*
	* if square if near end of map - think, that outside is neighbour road
	* if near neighbour road - add to result
	*/
	/*
	*  2     X - position of road sprite
	* 1X3
	*  0     0,1,2,3 - abstract numerating of neighbours
	*/

	int result = 0;

	if (positionY == FIELD_LENGTH - 1)
	{
		result += 1;
	}
	else
	if (Field[positionX][positionY+1] == 2)
	{
		result += 1;
	}

	if (positionX == FIELD_HIGH - 1)
	{
		result += 2;
	}
	else
	if (Field[positionX + 1][positionY] == 2)
	{
		result += 2;
	}

	if (positionY == 0)
	{
		result += 4;
	}
	else
	if (Field[positionX][positionY-1] == 2)
	{
		result += 4;
	}

	if (positionX == 0)
	{
		result += 8;
	}
	else
	if (Field[positionX - 1][positionY] == 2)
	{
		result += 8;
	}

	return result;
}

void Game::checkIntersections()
{
	/*
	* function of cheking intersection
	*/

	return;
}

void Game::checkTime(RenderWindow & window)
{
	/*
	* function of checking time
	*             if enough time passed - do some actions
	*
	* @param window - window of game
	*/

	// calc how much time passed
	double timer = myClock.getElapsedTime().asMilliseconds();

	// if enough time passed
	if (timer > MILLISECOND_FOR_ACTION)
	{
		// restart timer
		myClock.restart();
		
		// if game is not on pause
		if (!pause)
		{

			// move objects
			moveObjects(timer);

			// check bullets for deleting
			checkBullets();

			// check player gun for shooting and reloading
			checkPlayerGun(timer);

			//draw pictures
			drawObjects(window);
		}
	}
	
	return;
}

void Game::drawObjects(RenderWindow & window)
{
	/*
	* function of drawing sprites on screen
	*
	* @param window - game window
	*/

	// clear window, set background color Color::Black
	window.clear(Color::Black);

	// remember player global position (at map) and local (in window)
	pair < double, double > playerPositionInWindow = PlayerObject.getPositionInWindow();
	pair < double, double > playerPosition = PlayerObject.getPosition();

	// find coorditanes of square where player stay
	int positionInFieldY = (int)(playerPosition.first) / round(SQUARE_SIZE_PIXIL);
	int positionInFieldX = (int)(playerPosition.second) / round(SQUARE_SIZE_PIXIL);

	// find segments, which we have to check for drawing
	int _up = max(0, positionInFieldX - 8);
	int _down = min(FIELD_HIGH-1, positionInFieldX + 8);
	int _left = max(0, positionInFieldY - 14);
	int _right = min(FIELD_LENGTH-1, positionInFieldY + 14);

	// chech this rectangular
	for (int i = _up; i <= _down; i++)
	{
		for (int j = _left; j <= _right; j++)
		{
			// fing global position of current square 
			// and difference of global position player and current square
			double deltX = (j * SQUARE_SIZE_PIXIL) - playerPosition.first;
			double deltY = (i * SQUARE_SIZE_PIXIL) - playerPosition.second;
			
			// if this square have to be in window
			if (playerPositionInWindow.first + deltX > -SQUARE_SIZE_PIXIL && playerPositionInWindow.first + deltX < FIELD_LENGTH_PIXIL &&
				playerPositionInWindow.second + deltY > -SQUARE_SIZE_PIXIL && playerPositionInWindow.second + deltY < FIELD_HIGH_PIXIL)
			{
				// set ground sprite position and drow it 
				enviroment[0].setPosition(playerPositionInWindow.first + deltX, playerPositionInWindow.second + deltY);
				window.draw(enviroment[0]);

				// if square is road
				if (Field[i][j] == 2)
				{
					road[getRoadNumber(i, j)].setPosition(playerPositionInWindow.first + deltX, playerPositionInWindow.second + deltY);
					window.draw(road[getRoadNumber(i, j)]);
				}else

				// if this square is not tree
				if (Field[i][j] > 1)
				{
					// set sprite position and draw
					enviroment[Field[i][j]].setPosition(playerPositionInWindow.first + deltX, playerPositionInWindow.second + deltY);
					window.draw(enviroment[Field[i][j]]);
				}
			}
		}
	}

	// draw Player object
	PlayerObject.draw(window);

	// draw trees
	for (int i = _up; i <= _down; i++)
	{
		for (int j = _left; j <= _right; j++)
		{
			double deltX = (i * SQUARE_SIZE_PIXIL) - playerPosition.first;
			double deltY = (j * SQUARE_SIZE_PIXIL) - playerPosition.second;

			if (playerPositionInWindow.first + deltX > -SQUARE_SIZE_PIXIL && playerPositionInWindow.first + deltX < FIELD_LENGTH_PIXIL &&
				playerPositionInWindow.second + deltY > -SQUARE_SIZE_PIXIL && playerPositionInWindow.second + deltY < FIELD_HIGH_PIXIL)
			{
				if (Field[i][j] == 1)
				{
					enviroment[Field[i][j]].setPosition(playerPositionInWindow.first + deltX, playerPositionInWindow.second + deltY);
					window.draw(enviroment[Field[i][j]]);
				}
			}
		}
	}

	// check all bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		// get bullet global position
		pair < double, double > bulletPosition = bullets[i].getPosition();

		// find difference bullet and player positions
		double deltX = bulletPosition.first - playerPosition.first;
		double deltY = bulletPosition.second - playerPosition.second;

		// draw bullet
		bullets[i].draw(window, playerPositionInWindow.first + deltX, playerPositionInWindow.second + deltY);
	}

	// show new picture on display
	window.display();

	return;
}

void Game::moveObjects(double timer)
{
	/*
	* function of moving objects
	*
	* @param timer - how much time have been passed
	*/

	// move player
	PlayerObject.move(timer);

	// move all bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].move(timer);
	}

	return;
}

bool Game::switchEvent(Event & event)
{
	/*
	* function of checking event type and set reaction for event
	*
	* @param event - new event
	*
	* @return true - if it is time to finish programm
	*         false - we have to continue programm
	*/

	// if window close
	if (event.type == Event::Closed)
	{
		// it is time to finish programm
		return 1;
	}

	// if window lost focus (user switch to another window)
	if (event.type == Event::LostFocus)
	{
		// set pause
		makePause(1);
	}

	// if window gained focus (user switch to this window)
	if (event.type == Event::GainedFocus)
	{
		// stop pause
		makePause(0);
	}

	// if event of start/finish shooting
	if (equal(event, Shoot))
	{
		// set start/finish shooting
		shooting = (event.type == Shoot.type);
	}

	// if event of start/finish moving up
	if (equal(event, MoveUp))
	{
		// set start/finish moving up
		PlayerObject.setKeyUpPressed((event.type == MoveUp.type));
	}

	// if event of start/finish moving down
	if (equal(event, MoveDown))
	{
		// set start/finish moving down
		PlayerObject.setKeyDownPressed((event.type == MoveDown.type));
	}

	// if event of start/finish moving left
	if (equal(event, MoveLeft))
	{
		// set start/finish moving left
		PlayerObject.setKeyLeftPressed((event.type == MoveLeft.type));
	}

	// if event of start/finish moving right
	if (equal(event, MoveRight))
	{
		// set start/finish moving right
		PlayerObject.setKeyRightPressed((event.type == MoveRight.type));
	}
	
	// continue programm
	return 0;
}

void Game::makePause(bool isPause)
{
	/*
	* function of starting and stopping pause
	*
	* @param isPause - true if pause start 
	*                  flase if pause stop
	*/

	// set pause value
	pause = isPause;

	// restart timer
	myClock.restart();

	return;
}

void Game::saveGame()
{
	/*
	* function of rewriting save file
	*/

	return;
}

void Game::initBullet(Enemy & enemy)
{
	/*
	* function of initialization bullets by enemy
	*
	* @param  pointer to evemy object, which bullet created by
	*/

	return;
}

bool Game::initBullet()
{
	/*
	* function of initialization bullet by player
	*
	* @return true - if initialization completed
	*         false - if initialization failed
	*/

	// calculate bullet angle
	// bullet angle = player angle + random value in [- player weapon accurasy .. + player weapon accurasy]
	double angle = PlayerObject.getAngle() + PlayerWeapons[PlayerWeaponNumber].getAccurasy();

	// calculate global position of centre player sprite
	pair < double, double > playerPosition = PlayerObject.getPosition();
	playerPosition.first += PLAYER_SPRITE_LENGTH / 2;
	playerPosition.second += PLAYER_SPRITE_HIGH / 2;

	// set this position for bullet
	double positionX = playerPosition.first;
	double positionY = playerPosition.second;

	// set damage which bullet give
	int damage = PlayerWeapons[PlayerWeaponNumber].getDamage();

	// create new Bullet object
	Bullet newBullet;

	// if initializtion failed
	if (!newBullet.create(angle, positionX, positionY, 0, damage))
	{
		// return false - initialization failed
		return 0;
	}

	// push pullet to bullets list
	bullets.push_back(newBullet);

	// initialization completed
	return 1;
}

void Game::checkPlayerGun(double timer)
{
	/*
	* functio of checking player gun fo shooting and reloading
	*
	* @param timer - how mush time has been passed
	*/

	// increase timer inside the weapon
	PlayerWeapons[PlayerWeaponNumber].increaseTimer(timer);

	// if passed enough time for reloading and there is 0 ammo
	if (PlayerWeapons[PlayerWeaponNumber].getTimer() > PlayerWeapons[PlayerWeaponNumber].getReloadTime() && 
		PlayerWeapons[PlayerWeaponNumber].getCurrentAmmo() == 0)
	{
		// reload and set timer as zero
		PlayerWeapons[PlayerWeaponNumber].setCurrentAmmo(PlayerWeapons[PlayerWeaponNumber].getMaxAmmo());
		PlayerWeapons[PlayerWeaponNumber].setTimer(0.0);
	}

	// if player press shooting button and there is any bullet in ammo
	if (shooting && PlayerWeapons[PlayerWeaponNumber].getCurrentAmmo() > 0)
	{
		// if enough time has been passed
		if (PlayerWeapons[PlayerWeaponNumber].getTimer() > PlayerWeapons[PlayerWeaponNumber].getDelayBetweenShoots())
		{
			// shoot
			// set new ammo, set timer as zero
			PlayerWeapons[PlayerWeaponNumber].setCurrentAmmo(PlayerWeapons[PlayerWeaponNumber].getCurrentAmmo() - 1);
			PlayerWeapons[PlayerWeaponNumber].setTimer(0.0);
			
			// if bullet initialization failed
			if (!initBullet())
			{
				cerr << "Not init bullet\n";
			}
		}
	}

	// don`t make to mach value for timer
	if (PlayerWeapons[PlayerWeaponNumber].getTimer() > 10000)
	{
		PlayerWeapons[PlayerWeaponNumber].setTimer(10000);
	}

	return;
}

void Game::checkBullets()
{
	/*
	* function of checking bullets for deleting
	*/

	// look all bullets from last to first
	for (int i = bullets.size(); i; i--)
	{
		// if this bullets live too long
		if (bullets[i - 1].getTimeOfLife() > BULLET_MAX_LIFE)
		{
			// all bullets was before live too long to, delete them all
			bullets.erase(bullets.begin() + 0, bullets.begin() + i);

			break;
		}
	}

	return;
}

void Game::game(RenderWindow & window)
{
	/*
	* main function of game
	*
	* @param window - window of game
	*/

	// if game doesn`t load
	if (!loadGame())
	{
		// there if somthing wrong
		cerr << "Somthing go wrong...\n";
	}
			
	// create Event object
	Event event;

	cerr << "STH";

	// while user doesn`t close window 
	while (window.isOpen())
	{
		// if there is some event
		if (window.pollEvent(event))
		{
			// check event type
			if (switchEvent(event))
			{
				break;
			}
		}

		// check time for actions
		checkTime(window);
	}

	return;
}
