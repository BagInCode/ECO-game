#include "Weapon.h"


Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}

void Weapon::create(double _reload, double _shootDelay, double _bulletSpeed, double _accuracy, int _bulletsPerShoot, int _maxAmmo, int _damage, bool _isPlayerWeapon, vector < Bullet >* _bullets)
{
	/*
	* function of initialiation weapon
	*
	* @param reload - time of reload ammo
	*        shootDelay - delay between shoots
	*        bulletSpeed - speed of single bullet
	*        accuracy - bullet will get angle of player +- random value in [0..accuracy]
	*        bulletsPerShoot - count bullets in one shoot
	*        maxAmmo - maximal ammo
	*        damage - damage of single bullet
	*        isPlayerWeapon - true if it is players` weapon
	*        bullets - vector of bullets
	*/

	reload = _reload;
	shootDelay = _shootDelay;
	bulletSpeed = _bulletSpeed;
	accuracy = _accuracy;
	bulletsPerShoot = _bulletsPerShoot;
	maxAmmo = _maxAmmo;
	damage = _damage;
	isPlayerWeapon = _isPlayerWeapon;
	Bullets = _bullets;

	// set timer to value more than reload
	timer = reload + 1;

	// at start ammo is full
	currentAmmo = maxAmmo;

	return;
}

void Weapon::createBullet(pair < double, double > position, double angle, bool isPlayerTarget)
{
	/*
	* function of creating bullet and add to vector of bullets
	*
	* @param position - position of bullet
	*        angle - angle of moving
	*        isPlayerTarget - true, if target is player
	*/

	// create new object
	Bullet newBullet;

	// random value in range [-1..1]
	double accuracyValue = ((rand() % 101) - 50);
	accuracyValue /= 50;

	// caculate result bullet angle
	angle += accuracy * accuracyValue;

	// init bullet with new parametrs
	newBullet.create(position.first, position.second, angle, bulletSpeed, damage, !isPlayerWeapon);

	// add new bullet
	Bullets->push_back(newBullet);

	return;
}

void Weapon::startReload()
{
	/*
	* function of starting reloading
	*/

	// null ammo
	currentAmmo = 0;

	// start reload timer
	timer = 0;

	return;
}

void Weapon::increaseTimer(double _timer)
{
	/*
	* function of increasing weapon timer
	*
	* @param timer - how much time has been passed
	*/

	// increase timer
	timer += _timer;

	// if timer value is too big
	if (timer > reload)
	{
		// leave it in normal range
		timer = reload + 1;
	}

	return;
}

bool Weapon::shoot(pair < double, double > position, double angle, bool isPlayerTarget)
{
	/*
	* function of checking ammo and shooting
	*/

	// if ammo is empty
	if (currentAmmo == 0)
	{
		// if tine for reload has been passed
		if (timer > reload)
		{
			// reload ammo
			currentAmmo = maxAmmo;
		}
		else
		{
			// no amo -> can`t shoot
			return 0;
		}
	}

	// if there is some ammo and enough time passed for shooting
	if (timer > shootDelay)
	{
		// decrease ammo
		currentAmmo -= 1;

		// restart timer
		timer = 0;

		// create bullets
		for (int i = 0; i < bulletsPerShoot; i++)
		{
			createBullet(position, angle, 1);
		}

		return 1;
	}

	return 0;
}