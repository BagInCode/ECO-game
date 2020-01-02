#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>

#include "Player.h"
#include "Bullet.h"

#include "Constants.db"

using namespace std;
using namespace sf;

class Weapon
{
protected:
	double reload;
	double shootDelay;
	double timer;
	double bulletSpeed;
	double accuracy;
	
	int bulletsPerShoot;
	int maxAmmo;
	int currentAmmo;

	int damage;

	bool isPlayerWeapon;

public:
	Weapon();
	~Weapon();

	void increaseTimer(double _timer);
	void create(double _reload, double _shootDelay, double bulletSpeed, double _accuracy, int _bulletsPerShoot, int _maxAmmo, int _damage, bool _isPlayerWeapon);
	void shoot(Player & player, vector < Bullet > & Bullets);
	void createBullet(Player & player, vector < Bullet > & Bullets);
	void startReload();
};

