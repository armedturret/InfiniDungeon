#include "Damage.h"

#include <iostream>
#include "Random.h"

Damage::Damage()
{
}


Damage::~Damage()
{
}

void Damage::damageDoop(Creature& player)
{
	//Sudo code
	//int ran = Random::randInt(0, deffenderDex);

	//if (ran < (deffenderDex / 3)) {maff = attackerDmg - (deffenderDmg / 8)}
	//if ((deffenderDex / 3) < ran < ((deffenderDex / 3) * 2)) {maff = attackerDmg}
	//if (ran > ((deffenderDex / 3) * 2)) {maff = (attackerDmg + (deffenderDmg / 8) )}

	//z = maff - DeffenderDef
	//if (z < 0) {z = 0};
	//damageToApply = xY + z
}
