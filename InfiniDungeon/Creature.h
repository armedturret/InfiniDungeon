#pragma once
#include <DPE/TileSheet.h>
#include <DPE/SpriteBatch.h>
#include <DPE/DebugRender.h>
#include <iostream>

#include "Random.h"
#include "PathFinder.h"
#include "BresenhamAlgorithm.h"

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

	const int TILE_SIZE = 128;

protected:
	
	//returns true when arrived to next tile
	bool moveToNextTile(std::vector<Node>& path, float deltaTime);
	glm::vec2 m_position = glm::vec2(0.0f, 0.0f);

	int m_direction = 0; // 0 = left, 1 = up, 2 = right, 3 = down

	DPE::TileSheet m_tileSheet;
	DPE::ColorRGBA8 m_color;

	double m_animTime = 0.0f;

	PathFinder m_pathFinder;

	int m_health = 10;

	int m_maxHealth = 10;

	bool moving = false;

	int m_animTile = 0;

	BresenhamAlgorithm visionThing;
};

