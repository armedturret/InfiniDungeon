#pragma once

#include "Creature.h"

enum class BadGuyState {SEARCHING, ROAMING, ATTACKING};

class BadGuy : public Creature
{
public:
	BadGuy();
	~BadGuy();

	virtual void update(float deltaTime, Level& level);

	virtual void OnCreation(Level& level) {
		std::cout << "Creature " << m_name << "given no creation behavior" << std::endl;
	};

	//creature just walking
	virtual void RoamingBehavior(float deltaTime, Level& level) {
		std::cout << "Creature "<<m_name<<"given no roaming behavior" << std::endl;
	};

	//creature sees player
	virtual void AttackBehavior(float deltaTime, Level& level) {
		std::cout << "Creature " << m_name << "given no attack behavior" << std::endl;
	};

	//creature knows player there but can't see (Called when player teleports away or blinds enemy)
	virtual void SearchBehavior(float deltaTime, Level& level) {
		std::cout << "Creature " << m_name << "given no movement behavior" << std::endl;
	};

protected:
	std::string m_name;
	std::string m_lore;

	BadGuyState m_state;
};

