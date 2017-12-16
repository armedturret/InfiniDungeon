#include "Damage.h"

#include <iostream>
#include "Random.h"

Damage::Damage()
{
}


Damage::~Damage()
{
}

void Damage::damageDoop(Creature& attacker, Creature& defender)
{
	int attackDamage = 4; //Dunno how you want to do this. Base could be, say, 4, and increase as you equip weapons
	int defenderEvasion = 25; //This is a percent. It could start at 30%, and increase with items or something. Heavy armor would decrease it
	int defenderArmor = 1; //Do I need to say it?

	//Attacking enemy
	if (Random::randInt(1, 100) > defenderEvasion) {
		int damageDealt = Random::randInt(1, attackDamage) - defenderArmor;
		if (damageDealt > 0) {
			defender.applyDamage(damageDealt);
		}
	}

	//That should about do it, other than defining the variables, and making them to be changed when items are equipped, etc, and arrays for the enemy values and such.
}
