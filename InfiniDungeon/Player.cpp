#include "Player.h"

#include <DPE/ResourceManager.h>
#include <cmath>

#include "Random.h"

#include "BadGuy.h"

Player::Player():
			m_target(0.0f),
			m_nextTile(0.0f)
{
}


Player::~Player()
{
}

void Player::update(float deltaTime,
	const std::vector<std::vector<int>>& map,
	std::vector<std::vector<int>>& entMap,
	std::vector<BadGuy*>& badGuys,
	Player& jeff)
{
	if (m_inputManager->isKeyDown(SDL_BUTTON_LEFT) && !m_wasMouseDownPreviously) {
		if (!m_moving) {
			glm::vec2 worldCoords = m_camera->convertScreenToWorld(m_inputManager->getMouseCoords());
			m_target.x = floor(worldCoords.x / TILE_SIZE);
			m_target.y = floor(worldCoords.y / TILE_SIZE);

			//Test if coordinates are in map
			if (m_target.x >= 0.0f && m_target.y >= 0.0f && m_target.x < map.size() && m_target.y < map[0].size() &&map[m_target.y][m_target.x] != 1) {
				//test if they see an enemy
				m_enemiesSpotted = seesEnemy(badGuys, map, entMap);

				m_moving = true;
				
				m_startPosition.x = (m_position.x - TILE_SIZE / 2.0f) / TILE_SIZE;
				m_startPosition.y = (m_position.y - TILE_SIZE / 2.0f) / TILE_SIZE;

				if (m_startPosition.x == m_target.x
					&& m_startPosition.y == m_target.y)
					m_moving = false;

				//calculate the path
				m_path = m_pathFinder.pathBetweenPoints(m_startPosition, m_target, map);
			}
		}
		else {
		}
		//custom "press" rejection because the engine is buggy
		m_wasMouseDownPreviously = true;
	}
	else if(!m_inputManager->isKeyDown(SDL_BUTTON_LEFT)) {
		m_wasMouseDownPreviously = false;
	}

	if (m_inputManager->isKeyDown(SDLK_l) && !m_wasLDownPreviously) {
		//lore
		glm::vec2 worldCoords = m_camera->convertScreenToWorld(m_inputManager->getMouseCoords());
		m_target.x = floor(worldCoords.x / TILE_SIZE);
		m_target.y = floor(worldCoords.y / TILE_SIZE);

		//Test if coordinates are in map
		if (m_target.x >= 0.0f && m_target.y >= 0.0f && m_target.x < map.size() && m_target.y < map[0].size() && map[m_target.y][m_target.x] != 1) {
			
			for (BadGuy* b : badGuys) {
				if (Random::equals(floor(b->getPosition().x / TILE_SIZE) , m_target.x)
					&& Random::equals(floor(b->getPosition().y / TILE_SIZE) , m_target.y)) {
					std::cout << b->getLore() << std::endl;
				}
			}
		}
		m_wasLDownPreviously = true;
	}
	else if (!m_inputManager->isKeyDown(SDLK_l)) {
		m_wasLDownPreviously = false;
	}
	
	//move
	if (m_moving) {
		if (moveToNextTile(m_path, deltaTime)) {
			
			//stop if sees enemy
			if (seesEnemy(badGuys, map, entMap) && !m_enemiesSpotted) {
				m_enemiesSpotted = seesEnemy(badGuys, map, entMap);
				std::cout << "sup" << std::endl;
				//stop moving
				m_moving = false;
				m_animTime = 0.0;
				m_animTile = 0;
			}
			else if (m_enemiesSpotted && Random::equals(m_animTime, MAX_COMBAT_TILES)) {
				std::cout << "tup" << std::endl;
				//stop moving in combat
				m_moving = false;
				m_animTime = 0.0;
				m_animTile = 0;
			}
		}
		//checks if moveToNextTile has reached the end
		if (m_path.size() == 0) {
			m_moving = false;
			m_animTime = 0.0;
		}
	}
}

void Player::init(std::string texturePath, glm::ivec2 tileSheetSize, DPE::InputManager* inputManager, DPE::Camera2D* camera, glm::ivec2 startPos)
{
	m_health = 10;
	m_maxHealth = 10;

	DPE::GLTexture m_texture = DPE::ResourceManager::getTexture(texturePath);
	m_tileSheet.init(m_texture, tileSheetSize);

	m_inputManager = inputManager;

	m_camera = camera;

	m_position = glm::vec2(TILE_SIZE / 2.0f);
	m_position.x += startPos.x*TILE_SIZE;
	m_position.y += startPos.y*TILE_SIZE;
}

float Player::getDeltaFactor()
{
	if (m_moving)
		return 0.1f;
	else
		return 0.0f;
}

bool Player::seesEnemy(std::vector<BadGuy*> badGuys, const std::vector<std::vector<int>>& map, const std::vector<std::vector<int>>& entmap)
{
	for (BadGuy* b : badGuys) {
		if (seesPoint(map, entmap, b->getPosition()))
			return true;
	}

	return false;
}
