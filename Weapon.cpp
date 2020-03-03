#include "Weapon.h"


Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}

void Weapon::create(double _reload, double _shootDelay, double _bulletSpeed, double _accuracy, int _bulletsPerShoot, int _maxAmmo, int _damage, vector < Bullet >* _bullets)
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
	Bullets = _bullets;

	// null timer
	timer = 0;

	// at start ammo is full
	currentAmmo = maxAmmo;

	countBullets = maxAmmo * 4;

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
	newBullet.create(position.first, position.second, angle, bulletSpeed, damage, isPlayerTarget);

	// add new bullet
	Bullets->push_back(newBullet);

	return;
}

void Weapon::startReload()
{
	/*
	* function of starting reloading
	*/

	// move current bullets to inventar
	countBullets += currentAmmo;

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

	// if there are some bullets
	if (countBullets + currentAmmo > 0)
	{
		// increase timer
		timer += _timer;
	}

	// if timer value is too big
	if (timer > reload)
	{
		// leave it in normal range
		timer = reload + 1;

		// if ammo is empty
		if (currentAmmo == 0)
		{
			// null timer
			timer = 0;

			// set current ammo
			currentAmmo = min(countBullets, maxAmmo);

			// decrease count bullets
			countBullets -= currentAmmo;
		}
	}

	return;
}

bool Weapon::shoot(pair < double, double > position, double angle, bool isPlayerTarget)
{
	/*
	* function of checking ammo and shooting
	*/

	// if there is some ammo and enough time passed for shooting
	if (timer > shootDelay && currentAmmo > 0)
	{
		// decrease ammo
		if (!isPlayerTarget)
		{
			currentAmmo -= 1;
		}

		// restart timer
		timer = 0;

		// create bullets
		for (int i = 0; i < bulletsPerShoot; i++)
		{
			createBullet(position, angle, isPlayerTarget);
		}

		return 1;
	}

	return 0;
}

int Weapon::getCurrentAmmo()
{
	/*
	* function of getting current ammo
	*
	* @return current ammo
	*/

	return currentAmmo;
}

void Weapon::setCurrentAmmo(int _currentAmmo)
{
	/*
	* function of setting current ammo
	*
	* @param currentAmmo - new current ammo
	*/

	currentAmmo = _currentAmmo;
}

int Weapon::getCountBullets()
{
	/*
	* functionf of gettting count of bullets
	*
	* @return count of bullets
	*/

	return countBullets;
}

void Weapon::addBullets(int delt)
{
	/*
	* function of increasing count of bullets
	*
	* @param delt - increasing count
	*/

	countBullets += delt;
}