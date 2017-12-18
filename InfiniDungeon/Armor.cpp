#include "Armor.h"



Armor::Armor():
m_name("PapierPlate"),
m_lore("I'm invincible!!!!"),
m_defencePoints(1)
{
}

Armor::Armor(std::string armorName, std::string lore, int defencePoints):
m_name(armorName),
m_lore(lore),
m_defencePoints(defencePoints)
{
}


Armor::~Armor()
{
}
