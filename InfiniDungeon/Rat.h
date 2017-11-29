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
		Player& jeff) {
		//std::cout << "Creature " << m_name << " given no attack behavior" << std::endl;
	};

	//creature knows player there but can't see (Called when player teleports away or blinds enemy)
	virtual void SearchBehavior(float deltaTime,
		const std::vector<std::vector<int>>& map,
		std::vector<std::vector<int>>& entMap,
		std::vector<BadGuy*>& badGuys,
		Player& jeff) {
		std::cout << "Creature " << m_name << " given no movement behavior" << std::endl;
	};
private:
	bool m_moving;

	std::vector<Node> m_path;
	
	double m_animTime = 0.0;

	glm::ivec2 m_target;
	glm::ivec2 m_startPosition;

	glm::vec2 m_nextTile;

	PathFinder pathFinder;
};