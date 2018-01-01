#pragma once
#include "Creature.h"

const int DAMAGE_VARIATION = 10;

class Damage
{
public:
	Damage();
	~Damage();

	int damageToDeal(const int& attackDamage, const int& defenderEvasion, const int& defenderArmor);
};

