#pragma once
#include <string>
class Weapon
{
public:
	Weapon();
	Weapon(std::string name, std::string lore, int attackPoints);
	~Weapon();

	std::string getName() const { return m_name; }
	std::string getLore() const { return m_lore; }
	int getAttackPoints() const { return m_attackPoints; }

private:
	std::string m_name;
	std::string m_lore;
	int m_attackPoints;
};

