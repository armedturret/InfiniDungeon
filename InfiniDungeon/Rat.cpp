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

	m_tileSheet.init(DPE::ResourceManager::getTexture("Data/Textures/Themes/Underdark/Enemies/" + m_name+".png"), glm::ivec2(4, 2));

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

	//move
	if (m_moving) {
		if (moveToNextTile(m_path, map, entMap, deltaTime)) {
			//do sight calculations
			if (seesPoint(map, entMap, jeff.getPosition())) {
				m_state = BadGuyState::ATTACKING;
				m_moving = false;
				m_animTime = 0.0;
				m_animTile = 0;
				m_path.clear();
			}
		}
		if (m_path.size() == 0) {
			m_moving = false;
			m_animTime = 0.0;
			m_animTile = 0;
		}
	}
}

void Rat::AttackBehavior(float deltaTime, const std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& entMap, std::vector<BadGuy*>& badGuys, Player & jeff)
{
	if (m_path.size() == 0) {
		//player is movement target
		m_target.x = floor(jeff.getPosition().x  / TILE_SIZE);
		m_target.y = floor(jeff.getPosition().y  / TILE_SIZE);

		m_startPosition.x = (m_position.x - TILE_SIZE / 2.0f) / TILE_SIZE;
		m_startPosition.y = (m_position.y - TILE_SIZE / 2.0f) / TILE_SIZE;

		m_path = m_pathFinder.pathBetweenPoints(m_startPosition, m_target, map);
		std::cout << m_path.size() << std::endl;
		m_moving = true;
	}

	if (m_moving) {
		if (moveToNextTile(m_path, map, entMap, deltaTime)) {
			//next to player
			if (Random::equals(floor(m_animTime), m_path.size() - 2)) {
				m_attacking = true;
				m_moving = false;
				m_animTime = 0.0;
				m_animTile = 0;
			}else			//do sight calculations
			if (!seesPoint(map, entMap, jeff.getPosition())) {
				m_state = BadGuyState::SEARCHING;
				m_moving = false;
				m_animTime = 0.0;
				m_animTile = 0;
				m_path.clear();
			}//recalculate path
			else {
				m_path.clear();

				//player is movement target
				m_target.x = floor(jeff.getPosition().x / TILE_SIZE);
				m_target.y = floor(jeff.getPosition().y / TILE_SIZE);

				m_startPosition.x = (m_position.x - TILE_SIZE / 2.0f) / TILE_SIZE;
				m_startPosition.y = (m_position.y - TILE_SIZE / 2.0f) / TILE_SIZE;

				m_path = m_pathFinder.pathBetweenPoints(m_startPosition, m_target, map);
			}
		}
	}
	if (m_attacking) {
		//calculate if within coordinates
		if (arePositionsAdjacent(m_position, jeff.getPosition()))
			std::cout << "oof" << std::endl;
		else {
			//restart player as movement target
			m_target.x = jeff.getPosition().x / TILE_SIZE;
			m_target.y = jeff.getPosition().y / TILE_SIZE;

			m_startPosition.x = (m_position.x - TILE_SIZE / 2.0f) / TILE_SIZE;
			m_startPosition.y = (m_position.y - TILE_SIZE / 2.0f) / TILE_SIZE;

			m_path = m_pathFinder.pathBetweenPoints(m_startPosition, m_target, map);
			m_moving = true;
			m_attacking = false;
			m_animTime = 0.0;
			m_animTile = 0;
		}
	}
}

void Rat::SearchBehavior(float deltaTime, const std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& entMap, std::vector<BadGuy*>& badGuys, Player & jeff)
{
	//go to last position it saw the player then give up
	//ignore the copy paste

	if (m_path.size() == 0) {

		//no need to recalculate target

		m_startPosition.x = (m_position.x - TILE_SIZE / 2.0f) / TILE_SIZE;
		m_startPosition.y = (m_position.y - TILE_SIZE / 2.0f) / TILE_SIZE;

		m_path = m_pathFinder.pathBetweenPoints(m_startPosition, m_target, map);
		m_moving = true;
	}

	//move
	if (m_moving) {
		if (moveToNextTile(m_path, map, entMap, deltaTime)) {
			//do sight calculations to see if found player
			if (seesPoint(map, entMap, jeff.getPosition())) {
				m_state = BadGuyState::ATTACKING;
				m_moving = false;
				m_animTime = 0.0;
				m_animTile = 0;
				m_path.clear();
			}
		}
		//give up search
		if (m_path.size() == 0) {
			m_state = BadGuyState::ROAMING;
			m_moving = false;
			m_animTime = 0.0;
			m_animTile = 0;
		}
	}
}
