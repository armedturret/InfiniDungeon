#pragma once
#include "BadGuy.h"
#include "PathFinder.h"

#include "BresenhamAlgorithm.h"

#include "Player.h"

class Rat : public BadGuy
{
public:
	Rat();
	~Rat();

	virtual void OnCreation(const std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& entMap);

	virtual void OnDeath(const std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& entMap) {
		std::cout << "Creature " << m_name << " given no death behavior" << std::endl;
	};

	//creature just walking
	virtual void RoamingBehavior(float deltaTime,
		const std::vector<std::vector<int>>& map,
		std::vector<std::vector<int>>& entMap,
		std::vector<BadGuy*>& badGuys,
		Player& jeff);

	//creature sees player
	virtual void AttackBehavior(float deltaTime,
		const std::vector<std::vector<int>>& map,
		std::vector<std::vector<int>>& entMap,
		std::vector<BadGuy*>& badGuys,
		Player& jeff);

	//creature knows player there but can't see (Called when player teleports away or blinds enemy)
	virtual void SearchBehavior(float deltaTime,
		const std::vector<std::vector<int>>& map,
		std::vector<std::vector<int>>& entMap,
		std::vector<BadGuy*>& badGuys,
		Player& jeff);
private:
	bool m_moving;
	bool m_attacking;

	std::vector<Node> m_path;

	BresenhamAlgorithm m_sight;

	glm::ivec2 m_target;
	glm::ivec2 m_startPosition;

	glm::vec2 m_nextTile;

	PathFinder pathFinder;
};