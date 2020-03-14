#include "Constants.db"
#include "Game.h"
#include "GameGraphicsManager.h"
#include "GameGraphicsManagerInterface.h"
#include "GameGraphicsManagerCraftingTable.h"
#include "GameEnvironmentManager.h"
#include "GameEnvironmentManagerStorage.h"
#include "IntersectionManager.h"
#include "WaveManager.h"

Game::Game() : rnd((unsigned int)time(NULL))
{
	graphics = new GraphicsManager;
	environment = new EnvironmentManager;
	waves = new WaveManager;
	intersectionManager = new IntersectionManager;
}

Game::~Game()
{
	delete graphics;
	delete environment;
	delete waves;
	delete intersectionManager;
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

	environment->initComponents(this);

	// load enviroment sprites
	graphics->initComponents(this);

	// init weapon pistol
	allPlayerWeapon[0].create(PISTOL_RELOAD_TIME, PISTOL_SHOOT_DELAY_TIME, PISTOL_BULLET_SPEED, PISTOL_ACCURASY, PISTOL_BULLET_PER_SHOOT, PISTOL_MAX_AMMO, PISTOL_DMG, &Bullets, &rnd);
	allPlayerWeapon[0].addBullets(4 * PISTOL_MAX_AMMO);

	// init weapon hunter double
	allPlayerWeapon[1].create(SHOTGUN_RELOAD_TIME, SHOTGUN_SHOOT_DELAY_TIME, SHOTGUN_BULLET_SPEED, SHOTGUN_ACCURASY, SHOTGUN_BULLET_PER_SHOOT, SHOTGUN_MAX_AMMO, SHOTGUN_DMG, &Bullets, &rnd);

	// init weapon AK
	allPlayerWeapon[2].create(AK_RELOAD_TIME, AK_SHOOT_DELAY_TIME, AK_BULLET_SPEED, AK_ACCURASY, AK_BULLET_PER_SHOOT, AK_MAX_AMMO, AK_DMG, &Bullets, &rnd);

	// init weapon minigan
	allPlayerWeapon[3].create(MINIGUN_RELOAD_TIME, MINIGUN_SHOOT_DELAY_TIME, MINIGUN_BULLET_SPEED, MINIGUN_ACCURASY, MINIGUN_BULLET_PER_SHOOT, MINIGUN_MAX_AMMO, MINIGUN_DMG, &Bullets, &rnd);

	// init weapon sniper
	allPlayerWeapon[4].create(SNIPER_RELOAD_TIME, SNIPER_SHOOT_DELAY_TIME, SNIPER_BULLET_SPEED, SNIPER_ACCURASY, SNIPER_BULLET_PER_SHOOT, SNIPER_MAX_AMMO, SNIPER_DMG, &Bullets, &rnd);

	// start with pistol
	currentWeaponPointer = 0;
	
	countsGrenades = 0;

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
		intersectionManager->checkIntersection(this);

		// check game for ending
		checkGameOver();

		// check enemy
		checkEnemyAlive();

		// draw
		graphics->draw(this, waves);

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

	for (int i = 0; i < int(grenades.size()); i++)
	{
		grenades[i].move(timer);
	}

	// move player
	if (graphics->drawSwitcher == 0 || graphics->drawSwitcher == 1)
	{
		playerObject.move(timer);
	}

	// if there are some bullets 
	if (Bullets.size() > 0)
	{
		for (int i = 0; i < int(Bullets.size()); i++)
		{
			// move bullet
			Bullets[i].move(timer);
		}
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

		isKeyAPressed = 0;
		isKeySPressed = 0;
		isKeyWPressed = 0;
		isKeyDPressed = 0;

		playerObject.setMovingVector(0, 0);
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

			isKeyAPressed = 0;
			isKeySPressed = 0;
			isKeyWPressed = 0;
			isKeyDPressed = 0;

			playerObject.setMovingVector(0, 0);
			playerShooting = 0;
			timer = 0;
			myClock.restart();
		}

		// if key A
		if (event.key.code == Keyboard::A)
		{
			// if key A has not been pressed
			if (!isKeyAPressed)
			{
				isKeyAPressed = 1;

				// set new speed vector, value 2 is out of possibility range, so Y-vector will be unchanged
				playerObject.updateMovingVector(-1, 2);
			}
		}

		// if key S
		if (event.key.code == Keyboard::S)
		{
			// if key S has not been pressed
			if (!isKeySPressed)
			{
				isKeySPressed = 1;

				// set new speed vector, value 2 is out of possibility range, so X-vector will be unchanged
				playerObject.updateMovingVector(2, 1);
			}
		}

		// if key W
		if (event.key.code == Keyboard::W)
		{
			// if key W has not been pressed
			if (!isKeyWPressed)
			{
				isKeyWPressed = 1;

				// set new speed vector, value 2 is out of possibility range, so X-vector will be unchanged
				playerObject.updateMovingVector(2, -1);
			}
		}

		// if key D
		if (event.key.code == Keyboard::D)
		{
			// if key D has not been pressed
			if (!isKeyDPressed)
			{
				isKeyDPressed = 1;

				// set new speed vector, value 2 is out of possibility range, so Y-vector will be unchanged
				playerObject.updateMovingVector(1, 2);
			}
		}

		// if key M
		if (event.key.code == Keyboard::M)
		{
			// drowing minimap/drawing game scene

			if (graphics->drawSwitcher == 0)
			{
				graphics->drawSwitcher = 1;
			}
			else if (graphics->drawSwitcher == 1)
			{
				graphics->drawSwitcher = 0;
			}
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

			environment->checkStoragesAction(this, playerPositionX, playerPositionY);

			if (graphics->drawSwitcher == 0)
			{
				if (environment->isNearCraftingTable(playerPositionX, playerPositionY))
				{
					graphics->drawSwitcher = 2;
					graphics->craftingTable->open(this);
				}
			}
			else if (graphics->drawSwitcher == 2)
			{
				graphics->drawSwitcher = 0;
			}
		}

		// if reload button pressed
		if (event.key.code == Keyboard::R)
		{
			// start reload
			allPlayerWeapon[currentWeaponPointer].startReload();
		}

		if (event.key.code == Keyboard::G)
		{
			if (countsGrenades == 0)
			{
				return;
			}

			countsGrenades--;

			Grenade newGranade;
			newGranade.create(playerObject, window);

			grenades.push_back(newGranade);
		}
	}

	if (event.type == Event::KeyReleased)
	{
		// if key A
		if (event.key.code == Keyboard::A)
		{
			// if key A has been pressed
			if (isKeyAPressed)
			{
				isKeyAPressed = 0;

				// set new speed vector, value 2 is out of possibility range, so Y-vector will be unchanged
				playerObject.updateMovingVector(1, 2);
			}
		}

		// if key S
		if (event.key.code == Keyboard::S)
		{
			// if key S has been pressed
			if (isKeySPressed)
			{
				isKeySPressed = 0;

				// set new speed vector, value 2 is out of possibility range, so X-vector will be unchanged
				playerObject.updateMovingVector(2, -1);
			}
		}

		// if key W
		if (event.key.code == Keyboard::W)
		{
			// if key W has been pressed
			if (isKeyWPressed)
			{
				isKeyWPressed = 0;
			
				// set new speed vector, value 2 is out of possibility range, so X-vector will be unchanged
				playerObject.updateMovingVector(2, 1);
			}
		}

		// if key D
		if (event.key.code == Keyboard::D)
		{
			// if key D has been pressed
			if (isKeyDPressed)
			{
				isKeyDPressed = 0;

				// set new speed vector, value 2 is out of possibility range, so Y-vector will be unchanged
				playerObject.updateMovingVector(-1, 2);
			}
		}
	}

	// if mouse button pressed
	if (event.type == Event::MouseButtonPressed)
	{
		// if LMB
		if (event.mouseButton.button == Mouse::Left)
		{
			if (graphics->drawSwitcher == 0)
			{
				playerShooting = 1;
			}
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

	checkGranades();

	graphics->update(this, timer);

	// increase weapon timer
	allPlayerWeapon[currentWeaponPointer].increaseTimer(timer);

	// action of shooting
	if (playerShooting)
	{
		allPlayerWeapon[currentWeaponPointer].shoot(playerObject.getPosition(), playerObject.getAngle(), 0);
	}

	// for all enemys
	for (int i = 0; i < int(Enemys.size()); i++)
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

	environment->update(timer);

	playerObject.isDamaged = max(playerObject.isDamaged - 1, 0);

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

	for (int i = 0; i < int(Enemys.size()); i++)
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
		result->randomizeState(&rnd);
	}

	// if next stay state
	if (next == 1)
	{
		// create new stay state
		result = new StayState();

		// randomize state
		result->randomizeState(&rnd);
	}

	// if next shoot state
	if (next == 2)
	{
		// create new shoot state
		result = new ShootState();

		// randomize state
		result->randomizeState(&rnd);
	}

	// if next run on random vector state
	if (next == 3)
	{
		// create new state
		result = new RunRandomVectorState();

		// randomize state
		result->randomizeState(&rnd);
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
	for (int i = 0; i < int(Enemys.size()); i++)
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

void Game::checkGranades()
{
	vector < Grenade > newGrenades;

	for (int i = 0; i < int(grenades.size()); i++)
	{
		if (grenades[i].timeToDelete())
		{
			continue;
		}

		newGrenades.push_back(grenades[i]);
	}

	grenades = newGrenades;

	for (int i = 0; i < int(grenades.size()); i++)
	{
		if (grenades[i].isDetonate())
		{
			for (int j = 0; j < int(Enemys.size()); j++)
			{
				double deltX = Enemys[j].getPosition().first - grenades[i].getPosition().first;
				double deltY = Enemys[j].getPosition().second - grenades[i].getPosition().second;

				double len = sqrt(deltX*deltX + deltY*deltY);

				if (len < GRENADE_RADIUS)
				{
					Enemys[j].getDamage(GRENADE_DMG);
				}
			}
		}
	}

	return;
}