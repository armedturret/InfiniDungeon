#pragma once
#include <string>
class Armor
{
public:
	Armor(std::string armorName, std::string lore, int defencePoints);
	~Armor();

	std::string getName() const { return m_name; }
	std::string getLore() const { return m_lore; }
	int getDefencePoints() const { return m_defencePoints; }

private:
	std::string m_name;
	std::string m_lore;
	int m_defencePoints;
};

