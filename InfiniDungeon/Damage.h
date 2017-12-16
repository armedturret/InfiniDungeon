#pragma once
#include "Creature.h"

class Damage
{
public:
	Damage();
	~Damage();

	int damageToDeal(Creature& attacker, Creature& defender);
};

