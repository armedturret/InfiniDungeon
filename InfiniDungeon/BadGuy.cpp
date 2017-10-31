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

void BadGuy::update(float deltaTime, Level & level)
{
	if (m_state == BadGuyState::ROAMING) {
		roamingBehavior(deltaTime, level);
	}
	else if (m_state == BadGuyState::SEARCHING) {
		searchBehavior(deltaTime, level);
	}
	else if (m_state == BadGuyState::ATTACKING) {
		attackBehavior(deltaTime, level);
	}
}
