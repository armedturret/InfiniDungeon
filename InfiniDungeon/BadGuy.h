#pragma once

#include "Creature.h"
enum class BadGuyState {SEARCHING, ROAMING, ATTACKING};

class BadGuy : public Creature
{
public:
	BadGuy();
	~BadGuy();
	
	void Spawn(glm::vec2 pos, const std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& entMap);

	/*virtual void update(float deltaTime,
		const std::vector<std::vector<int>>& map,
		std::vector<std::vector<int>>& entMap,
		std::vector<BadGuy*>& badGuys,
		Player& jeff)override;*/

	virtual void OnCreation(const std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& entMap) {
		std::cout << "Creature " << m_name << " given no creation behavior" << std::endl;
	};

	virtual void OnDeath(const std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& entMap) {
		std::cout << "Creature " << m_name << " given no death behavior" << std::endl;
	};

	//creature just walking
	virtual void RoamingBehavior(float deltaTime,
		const std::vector<std::vector<int>>& map,
		std::vector<std::vector<int>>& entMap,
		std::vector<BadGuy*>& badGuys,
		Player& jeff) {
		std::cout << "Creature "<<m_name<<" given no roaming behavior" << std::endl;
	};

	//creature sees player
	virtual void AttackBehavior(float deltaTime,
		const std::vector<std::vector<int>>& map,
		std::vector<std::vector<int>>& entMap,
		std::vector<BadGuy*>& badGuys,
		Player& jeff) {
		std::cout << "Creature " << m_name << " given no attack behavior" << std::endl;
	};

	//creature knows player there but can't see (Called when player teleports away or blinds enemy)
	virtual void SearchBehavior(float deltaTime,
		const std::vector<std::vector<int>>& map,
		std::vector<std::vector<int>>& entMap,
		std::vector<BadGuy*>& badGuys,
		Player& jeff) {
		std::cout << "Creature " << m_name << " given no movement behavior" << std::endl;
	};

	std::string getName() const { return m_name; }
	std::string getLore() const { return m_lore; }
protected:
	std::string m_name;
	std::string m_lore;

	BadGuyState m_state;
};

