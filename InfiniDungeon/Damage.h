#pragma once
#include "Creature.h"

class Damage
{
public:
	Damage();
	~Damage();

	void damageDoop(Creature& attacker, Creature& defender);
};

