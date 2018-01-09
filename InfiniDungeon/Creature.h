#pragma once
#include <DPE/TileSheet.h>
#include <DPE/SpriteBatch.h>
#include <DPE/DebugRender.h>
#include <iostream>

#include "Random.h"
#include "PathFinder.h"
#include "BresenhamAlgorithm.h"
#include "Armor.h"
#include "Weapon.h"
class Player;
class BadGuy;

//idle is in between turns
//waiting is skip a turn
//moving and fighting are 
enum class CreatureState{IDLE, WAITING, MOVING, FIGHTING};

class Creature
{
public:
	Creature();
	~Creature();
	void update(CreatureState turnState,
		const float& progressThroughTurn,
		const int& turnsSinceStart,
		const std::vector<std::vector<int>>& map,
		std::vector<std::vector<int>>& entMap,
		std::vector<BadGuy*>& badGuys,
		Player& player);

	void draw(DPE::SpriteBatch& m_spriteBatch);

	int getEvade() const { return m_evade; }
	int getHealth() const { return m_health; }
	int getMaxHealth() const { return m_maxHealth; }

	glm::vec2 getPosition() const { return m_position; }

	void applyDamage(const int& damage);

	const int TILE_SIZE = 128;

	Armor getArmor() const { return m_armor; }
	Weapon getWeapon() const { return m_weapon; }

protected:
	
	void performTurn(CreatureState turnState,
		const float& progressThroughTurn,
		const int& turnsSinceStart,
		const std::vector<std::vector<int>>& map,
		std::vector<std::vector<int>>& entMap,
		std::vector<BadGuy*>& badGuys,
		Player& player);

	virtual void onAttack(const float& progressThroughTurn,
		const int& turnsSinceStart,
		const std::vector<std::vector<int>>& map,
		std::vector<std::vector<int>>& entMap,
		std::vector<BadGuy*>& badGuys,
		Player& player) {
		std::cout << "oof" << std::endl;
	}

	virtual void onMove(const float& progressThroughTurn,
		const int& turnsSinceStart,
		const std::vector<std::vector<int>>& map,
		std::vector<std::vector<int>>& entMap,
		std::vector<BadGuy*>& badGuys,
		Player& player);

	virtual void onBeginSequence(const float& progressThroughTurn,
		const int& turnsSinceStart,
		const std::vector<std::vector<int>>& map,
		std::vector<std::vector<int>>& entMap,
		std::vector<BadGuy*>& badGuys,
		Player& player) {
		std::cout << "oof" << std::endl;
	}

	virtual void onBeginTurn(const float& progressThroughTurn,
		const int& turnsSinceStart,
		const std::vector<std::vector<int>>& map,
		std::vector<std::vector<int>>& entMap,
		std::vector<BadGuy*>& badGuys,
		Player& player) {
		std::cout << "oof" << std::endl;
	}

	virtual void onIdle(const float& progressThroughTurn,
		const int& turnsSinceStart,
		const std::vector<std::vector<int>>& map,
		std::vector<std::vector<int>>& entMap,
		std::vector<BadGuy*>& badGuys,
		Player& player) {
	}

	void setTarget(const std::vector<std::vector<int>>& map,
		std::vector<std::vector<int>>& entMap,
		glm::vec2 target);

	void moveTowardsTile(const glm::vec2& nodePosOne,
		const glm::vec2& nodePosTwo,
		const std::vector<std::vector<int>>& map,
		std::vector<std::vector<int>>& entmap,
		int fractionBetweenTwo);
	//returns true when arrived to next tile
	//bool moveToNextTile(std::vector<Node>& path, const std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& entmap, float deltaTime);
	//uses raw positions and uses Bresenham
	bool seesPoint(const std::vector<std::vector<int>>& map, const std::vector<std::vector<int>>& entmap, glm::vec2 end);

	glm::vec2 m_position = glm::vec2(0.0f, 0.0f);

	//used for animation
	glm::vec2 m_nextPosition = glm::vec2(0.0f);

	int m_direction = 0; // 2 = left, 1 = right

	DPE::TileSheet m_tileSheet;
	DPE::ColorRGBA8 m_color;

	std::vector<Node> m_path;

	PathFinder m_pathFinder;

	//frames in between animations
	double m_animSpeed = 5;

	float m_animTime = 0.0;

	int m_evade = 0;

	int m_health = 10;

	int m_maxHealth = 10;

	bool m_shouldWait = false;

	int m_animTile = 0;

	Armor m_armor;
	Weapon m_weapon;

	BresenhamAlgorithm visionThing;
};

