#include "Rat.h"

#include "Random.h"
#include <DPE/ResourceManager.h>

#include <cmath>

Rat::Rat()
{
}


Rat::~Rat()
{
}

void Rat::OnCreation(const std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& entMap)
{
	m_health = 10;
	m_maxHealth = 10;

	m_lore = "These bloated rodents have become lazy and lethargic from time spent in a dungeon with scores of heroes come to feed them.";
	m_name = "Giant Rat";

	m_tileSheet.init(DPE::ResourceManager::getTexture("Data/Textures/Themes/Basic/Enemies/" + m_name+".png"), glm::ivec2(4, 2));

	m_animTile = 1;

	m_moving = false;
}

void Rat::RoamingBehavior(float deltaTime,
	const std::vector<std::vector<int>>& map,
	std::vector<std::vector<int>>& entMap,
	std::vector<BadGuy*>& badGuys,
	Player& jeff) {
	if (!m_moving) {
		while (true) {
			m_target.y = Random::randInt(1, map.size() - 1);
			m_target.x = Random::randInt(1, map[0].size() - 1);
			if (map[m_target.y][m_target.x] == 0) {
				m_moving = true;

				m_startPosition.x = (m_position.x - TILE_SIZE / 2.0f) / TILE_SIZE;
				m_startPosition.y = (m_position.y - TILE_SIZE / 2.0f) / TILE_SIZE;

				if (m_startPosition.x == m_target.x
					&& m_startPosition.y == m_target.y)
					m_moving = false;

				m_path = pathFinder.pathBetweenPoints(m_startPosition, m_target, map);
				break;
			}
		}
	}

	if (m_moving) {
		if (moveToNextTile(m_path, deltaTime)) {
			std::cout << "intermediate" << moveToNextTile(m_path, deltaTime) << std::endl;
		}
		if (m_path.size() == 0) {
			std::cout << "End" << std::endl;
			m_moving = false;
			m_animTime = 0.0;
		}
	}
}