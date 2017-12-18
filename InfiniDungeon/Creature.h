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

class Creature
{
public:
	Creature();
	~Creature();
	virtual void update(float deltaTime,
		const std::vector<std::vector<int>>& map,
		std::vector<std::vector<int>>& entMap,
		std::vector<BadGuy*>& badGuys,
		Player& jeff) {
		std::cout << "Creature given no update behavior" << std::endl;
	};

	void draw(DPE::SpriteBatch& m_spriteBatch);

	glm::vec2 getPosition() const { return m_position; }

	int getHealth() const { return m_health; }

	void applyDamage(const int& damage);

	const int TILE_SIZE = 128;

	Armor getArmor() const { return m_armor; }
	Weapon getWeapon() const { return m_weapon; }

protected:
	
	//returns true when arrived to next tile
	bool moveToNextTile(std::vector<Node>& path, const std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& entmap, float deltaTime);
	//uses raw positions and uses Bresenham
	bool seesPoint(const std::vector<std::vector<int>>& map, const std::vector<std::vector<int>>& entmap, glm::vec2 end);

	glm::vec2 m_position = glm::vec2(0.0f, 0.0f);

	//used for animation
	glm::vec2 m_nextPosition = glm::vec2(0.0f);

	int m_direction = 0; // 2 = left, 1 = right

	DPE::TileSheet m_tileSheet;
	DPE::ColorRGBA8 m_color;

	double m_animTime = 0.0;

	PathFinder m_pathFinder;

	//frames in between animations
	double m_animSpeed = 5;

	int m_health = 10;

	int m_maxHealth = 10;

	bool moving = false;

	int m_animTile = 0;

	Armor m_armor;
	Weapon m_weapon;

	BresenhamAlgorithm visionThing;
};

