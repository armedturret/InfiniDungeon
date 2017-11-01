#pragma once
#include "BadGuy.h"
class Rat : public BadGuy
{
public:
	Rat();
	~Rat();

	virtual void OnCreation(const std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& entMap);

	//creature just walking
	virtual void RoamingBehavior(float deltaTime, const std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& entMap) {
		//std::cout << "Creature " << m_name << " given no roaming behavior"<< std::endl;
	};

	//creature sees player
	virtual void AttackBehavior(float deltaTime, const std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& entMap) {
		std::cout << "Creature " << m_name << " given no attack behavior" << std::endl;
	};

	//creature knows player there but can't see (Called when player teleports away or blinds enemy)
	virtual void SearchBehavior(float deltaTime, const std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& entMap) {
		std::cout << "Creature " << m_name << " given no movement behavior" << std::endl;
	};
};

