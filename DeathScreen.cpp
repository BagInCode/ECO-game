#include "DeathScreen.h"
#include <chrono>
#include <thread>


DeathScreen::DeathScreen()
{
}


DeathScreen::~DeathScreen()
{
}

void DeathScreen::initComponents()
{
	/*
	* function of initialization 
	*/

	// load fonts
	font.loadFromFile(DEATH_SCREEN_FONT_PATH);
	
	// set font to text
	DeathText.setFont(font);

	// start clocks
	myClock.restart();

	return;
}

void DeathScreen::firstScene(RenderWindow* window)
{
	/*
	* function of showing slowly apearing text
	*
	* @param window - game window
	*/

	// set timer of scene
	timer = 0;

	//  set color of text
	color = Color::Red;

	// set text string, size and position
	DeathText.setString("You DIE!");
	DeathText.setCharacterSize(325);
	DeathText.setPosition((WINDOW_LENGTH - DeathText.getGlobalBounds().width) / 2, 100);

	// for time of this scene
	while (timer < DEATH_SCREEN_FIRST_SCENE_TIME)
	{
		// increase timer
		timer += myClock.restart().asMilliseconds();
		
		// set color opacity
		color.a = Uint8(round(255*sin(((acos(-1) / 2) * timer) / DEATH_SCREEN_FIRST_SCENE_TIME)));
		
		// set color for text
		DeathText.setFillColor(color);

		// clear window, draw text and show it
		window->clear(Color::Black);
		window->draw(DeathText);
		window->display();
	}

	return;
}

void DeathScreen::secondScene(RenderWindow* window)
{
	/*
	* function of showing static text
	*
	* @param window - game window
	*/

	// set color
	color = Color::Red;

	// set color for text
	DeathText.setFillColor(Color::Red);

	// clear window, draw text and show it
	window->clear(Color::Black);
	window->draw(DeathText);
	window->display();

	// wait for some time...
	this_thread::sleep_for(chrono::milliseconds(DEATH_SCREEN_SECOND_SCENE_TIME));

	return;
}

string DeathScreen::toString(int val)
{
	/*
	* function of converting positiove integer value to string
	*
	* @param val - positiove integer value
	*
	* @return string form of this value
	*/

	// if value is 0
	if (val == 0)
	{
		// return string with 0
		return "0";
	}

	// create string for result
	string res;

	// while value grethe than zero
	while (val > 0)
	{
		// add to result last digit
		res += char('0' + val % 10);

		// remove last digit from value
		val /= 10;
	}

	// reverse string
	reverse(res.begin(), res.end());

	return res;
}

void DeathScreen::showResult(vector < int > parametrs, RenderWindow* window)
{
	/*
	* function of showing result of game on screen
	*
	* @param parametrs - result data
	*        window - game window
	*/

	// clear window
	window->clear(Color::Black);

	// create string with result
	string information = "Result:\n\n";

	// add information
	information = information + "Field squares visible ............. " + toString(parametrs[0]) + "/" + toString(FIELD_SIZE*FIELD_SIZE) + "\n";
	information = information + "Count of waves ..................... " + toString(parametrs[1]) + "\n";
	information = information + "Enemys killed ......................... " + toString(parametrs[2]) + "\n";
	information = information + "             by Pistol ...................... " + toString(parametrs[3]) + "\n";
	information = information + "             by Shotgun ................. " + toString(parametrs[4]) + "\n";
	information = information + "             by AK ............................ " + toString(parametrs[5]) + "\n";
	information = information + "             by Minigun .................. " + toString(parametrs[6]) + "\n";
	information = information + "             by Sniper ..................... " + toString(parametrs[7]) + "\n\n";
	information = information + "             by grenade ................. " + toString(parametrs[2] - parametrs[3] - parametrs[4] - parametrs[5] - parametrs[6] - parametrs[7]) + "\n";
	
	information = information + "Press any key to continue...";

	// set color, size, position and string to text
	DeathText.setFillColor(Color::White);
	DeathText.setCharacterSize(30);
	DeathText.setString(information);
	DeathText.setPosition(15, 15);

	// draw and show text
	window->draw(DeathText);
	window->display();

	return;
}

void DeathScreen::process(vector < int > parametrs, RenderWindow* window)
{
	/*
	* main function of DeathScreen
	*
	* @param parametrs - final result data
	*        window - game window
	*/

	// init cimponents
	initComponents();

	// show first scene
	firstScene(window);

	// show second scene
	secondScene(window);

	// show result
	showResult(parametrs, window);
	
	// create event
	Event event;

	while (1)
	{
		// if there is some event
		if (window->pollEvent(event))
		{
			// if wvwnt of key pressing
			if (event.type == Event::KeyPressed)
			{
				// end function
				return;
			}

			// if window close
			if (event.type == Event::Closed)
			{
				// close window
				window->close();

				// end function
				return;
			}
		}
	}

	return;
}