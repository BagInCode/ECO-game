#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>
#include <random>

#include "Player.h"
#include "Bullet.h"

#include "Constants.db"

using namespace std;
using namespace sf;

class Weapon
{
private:
	double reload;
	double shootDelay;
	double timer;
	double bulletSpeed;
	double accuracy;
	
	int bulletsPerShoot;
	int maxAmmo;
	int currentAmmo;

	int damage;

	int countBullets;

	vector < Bullet >* Bullets;

public:

	mt19937* rnd;

	int reloadEngrams;
	int accuracyEngrams;
	int damageEngrams;
	int gainingAmmoEngrams;

	Weapon();
	~Weapon();

	void increaseTimer(double _timer);
	void create(double _reload, double _shootDelay, double bulletSpeed, double _accuracy, int _bulletsPerShoot, 
		int _maxAmmo, int _damage, vector < Bullet >* _bullets, mt19937* _rnd);

	bool shoot(pair < double, double > position, double angle, bool isPlayerTarget, int weaponType = -1);
	void createBullet(pair < double, double > position, double angle, bool isPlayerTarget, int weaponType);
	
	int getCountBullets();
	void addBullets(int delt);
	void setBullets(int newBullets);

	void startReload();

	double getReloadingTime();
	double getTimer();
	int getCurrentAmmo();

	void setCurrentAmmo(int _currentAmmo);
	
	void improveReloading(double multiplayer);
	void improveAccuracy(double multiplayer);
	void improveDamage(int add);
	void improveAmmoLoot();
};

