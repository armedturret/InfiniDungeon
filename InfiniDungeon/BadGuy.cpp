#include "BadGuy.h"

#include "Player.h"

BadGuy::BadGuy():
	m_state(BadGuyState::ROAMING),
	m_name("YorpDorp"),
	m_lore("The crazed pumpkin man with claws.")
{
}


BadGuy::~BadGuy()
{
}

void BadGuy::Spawn(glm::vec2 pos, const std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& entMap)
{
	m_position = glm::vec2(TILE_SIZE / 2.0f);
	m_position.x += pos.x*TILE_SIZE;
	m_position.y += pos.y*TILE_SIZE;

	OnCreation(map, entMap);
}

void BadGuy::update(float deltaTime,
	const std::vector<std::vector<int>>& map,
	std::vector<std::vector<int>>& entMap,
	std::vector<BadGuy*>& badGuys,
	Player& jeff)
{
	if (m_state == BadGuyState::ROAMING) {
		RoamingBehavior(deltaTime, map, entMap, badGuys, jeff);
	}
	else if (m_state == BadGuyState::SEARCHING) {
		SearchBehavior(deltaTime, map, entMap, badGuys, jeff);
	}
	else if (m_state == BadGuyState::ATTACKING) {
		AttackBehavior(deltaTime, map, entMap, badGuys, jeff);
	}

	//kill
	if (m_health <= 0)
		OnDeath(map, entMap);
}

bool BadGuy::arePositionsAdjacent(glm::vec2 posOne, glm::vec2 posTwo)
{
	//ugh
	return ((Random::equals(posOne.x, posTwo.x - (double)TILE_SIZE) || Random::equals(posOne.x, posTwo.x + (double)TILE_SIZE)) && Random::equals(posOne.y, posTwo.y))||
		((Random::equals(posOne.y, posTwo.y - (double)TILE_SIZE) || Random::equals(posOne.y, posTwo.y + (double)TILE_SIZE)) && Random::equals(posOne.x, posTwo.x))||
		((Random::equals(posOne.x, posTwo.x - (double)TILE_SIZE) || Random::equals(posOne.x, posTwo.x + (double)TILE_SIZE)) && ((Random::equals(posOne.y, posTwo.y - (double)TILE_SIZE))|| Random::equals(posOne.y, posTwo.y + (double)TILE_SIZE)));
}
