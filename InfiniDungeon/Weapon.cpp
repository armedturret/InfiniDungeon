#include "Weapon.h"



Weapon::Weapon():
m_name("stabbyThing"),
m_lore("W0W0W0W"),
m_attackPoints(9000)
{
}

Weapon::Weapon(std::string name, std::string lore, int attackPoints):
m_name(name),
m_lore(lore),
m_attackPoints(attackPoints)
{
}


Weapon::~Weapon()
{
}
