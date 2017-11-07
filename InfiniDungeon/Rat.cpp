#include "Rat.h"

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

	m_lore = "A nasty sewer creature that somehow grew to the size of a man.";
	m_name = "Giant Rat";

	m_tileSheet.init(DPE::ResourceManager::getTexture("Data/Textures/Themes/Basic/Enemies/" + m_name+".png"), glm::ivec2(4, 2));

	m_animTile = 1;

	m_moving = false;
}

void Rat::RoamingBehavior(float deltaTime, const std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& entMap) {
	if (!m_moving) {
		while (true) {
			m_target.y = randInt(1, map.size() - 1);
			m_target.x = randInt(1, map[0].size() - 1);
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

	if (m_moving && deltaTime > 0.0f) {
		m_animTime += deltaTime;
		//calculate players position in path
		glm::vec2 calcPos;
		if (m_animTime - 1 <= m_path.size()) {
			if (floor(m_animTime) == 0)
				calcPos = m_startPosition;
			else
				calcPos = m_path[m_path.size() - floor(m_animTime)].getPosition();

			if (floor(m_animTime) < m_path.size())
				m_nextTile = m_path[m_path.size() - floor(m_animTime) - 1].getPosition();

			//check if nextTile is door
			if (map[m_nextTile.y][m_nextTile.x] == 2) {
				entMap[m_nextTile.y][m_nextTile.x] = 1;
			}
			//make sure to close previous doors
			if (m_path.size() - floor(m_animTime) + 1 < m_path.size()) {
				glm::vec2 prevPos = m_path[m_path.size() - floor(m_animTime) + 1].getPosition();
				if (map[prevPos.y][prevPos.x] == 2) {
					entMap[prevPos.y][prevPos.x] = 0;
				}
			}
			//Check if start pos was a door
			if (map[m_startPosition.y][m_startPosition.x] == 2 && m_nextTile.y - calcPos.y < 0.05f && m_nextTile.x - calcPos.x < 0.05f) {
				entMap[m_startPosition.y][m_startPosition.x] = 0;
			}

			if (m_nextTile.x == calcPos.x + 1)
				m_direction = 2;
			else if (m_nextTile.x == calcPos.x - 1)
				m_direction = 1;

			m_position.x = ((m_nextTile.x - calcPos.x) * (m_animTime - floor(m_animTime)) + calcPos.x) * TILE_SIZE + TILE_SIZE / 2.0f;
			m_position.y = ((m_nextTile.y - calcPos.y) * (m_animTime - floor(m_animTime)) + calcPos.y) * TILE_SIZE + TILE_SIZE / 2.0f;

			m_animTile = (int)floor(m_animTime) % 3;

			m_animTile += 3;

			if (m_position.x == m_target.x * TILE_SIZE + TILE_SIZE / 2.0f && m_target.y*TILE_SIZE + TILE_SIZE / 2.0f == m_position.y) {
				m_moving = false;
				m_animTime = 0.0f;
				m_animTile = 3;
			}
		}

	}
	else if (m_moving && m_animTime > 0.0f) {
		m_animTile = 3;
		m_animTime = round(m_animTime);

		glm::vec2 calcPos(0.0f);

		if (floor(m_animTime) == 0)
			calcPos = m_startPosition;
		else
			calcPos = m_path[m_path.size() - floor(m_animTime)].getPosition();

		m_position.x = calcPos.x * TILE_SIZE + TILE_SIZE / 2.0f;
		m_position.y = calcPos.y * TILE_SIZE + TILE_SIZE / 2.0f;
	}
}