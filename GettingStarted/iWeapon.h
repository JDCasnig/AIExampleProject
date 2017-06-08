#ifndef _iWeapon_HG_
#define _iWeapon_HG_

#include <string>

class iWeapon
{
	enum eWeaponType
	{
		NONE,
		MELEE,
		RANGED,
		THROWN
	};

	iWeapon();
	~iWeapon();

	void Attack();

	eWeaponType weapon;
	std::string weaponName;
	int lowDamage;
	int highDamage;

};

#endif