#include "BadGuy.h"



BadGuy::BadGuy():
	m_state(BadGuyState::ROAMING),
	m_name("YorpDorp"),
	m_lore("The crazed pumpkin man with claws.")
{
}


BadGuy::~BadGuy()
{
}

void BadGuy::update(float deltaTime, const std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& entMap)
{
	if (m_state == BadGuyState::ROAMING) {
		RoamingBehavior(deltaTime, map, entMap);
	}
	else if (m_state == BadGuyState::SEARCHING) {
		SearchBehavior(deltaTime, map, entMap);
	}
	else if (m_state == BadGuyState::ATTACKING) {
		AttackBehavior(deltaTime, map, entMap);
	}
}
