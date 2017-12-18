#include "Weapon.h"



Weapon::Weapon(std::string name, std::string lore, int attackPoints):
m_name(name),
m_lore(lore),
m_attackPoints(attackPoints)
{
}


Weapon::~Weapon()
{
}
