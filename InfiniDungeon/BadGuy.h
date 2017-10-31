#pragma once

#include "Creature.h"

enum class BadGuyState {SEARCHING, ROAMING, ATTACKING};

class BadGuy : public Creature
{
public:
	BadGuy();
	~BadGuy();

	virtual void update(float deltaTime, Level& level);

	//creature just walking
	virtual void roamingBehavior() {
		std::cout << "Creature "<<m_name<<"given no roaming behavior" << std::endl;
	};

	//creature sees player
	virtual void attackBehavior() {
		std::cout << "Creature " << m_name << "given no attack behavior" << std::endl;
	};

	//creature knows player there but can't see (Called when player teleports away or blinds enemy)
	virtual void searchBehavior() {
		std::cout << "Creature " << m_name << "given no movement behavior" << std::endl;
	};

protected:
	std::string m_name;
	std::string m_lore;

	BadGuyState m_state;
};

