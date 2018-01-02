#include "Damage.h"

#include <iostream>
#include "Random.h"

Damage::Damage()
{
}


Damage::~Damage()
{
}

int Damage::damageToDeal(const int& attackDamage, const int& attackEvade, const int& defenderEvasion, const int& defenderArmor)
{
	//Dunno how you want to do this. Base could be, say, 4, and increase as you equip weapons
	//This is a percent. It could start at 30%, and increase with items or something. Heavy armor would decrease it
	 //Do I need to say it?

	//Attacking enemy
	if (Random::randInt(1, 100 + attackEvade) > defenderEvasion) {
		int damageDealt = Random::randInt(attackDamage - DAMAGE_VARIATION, attackDamage + DAMAGE_VARIATION / 2) - defenderArmor;
		if (damageDealt < 0)
			damageDealt = 0;
		return damageDealt;
	}
	else {
		return 0;
	}

	//That should about do it, other than defining the variables, and making them to be changed when items are equipped, etc, and arrays for the enemy values and such.
}
