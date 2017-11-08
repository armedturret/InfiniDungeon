#include "Player.h"

#include <DPE/ResourceManager.h>
#include <cmath>

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
			//prevents glitch where they get stuck between tiles
			m_position.x = m_nextTile.x * TILE_SIZE + TILE_SIZE / 2.0f;
			m_position.y = m_nextTile.y * TILE_SIZE + TILE_SIZE / 2.0f;

			m_animTime = 0.0f;
			m_animTile = 3;
			m_moving = false;
		}
		//custom "press" rejection because the engine is buggy
		m_wasMouseDownPreviously = true;
	}
	else if(!m_inputManager->isKeyDown(SDL_BUTTON_LEFT)) {
		m_wasMouseDownPreviously = false;
	}
	if (m_moving && deltaTime > 0.0f) {
		m_animTime += deltaTime;
		//use trunc to fix wierd rounding glitch
		if ((int)m_animTime == m_path.size()) {
			m_position.x = m_nextTile.x * TILE_SIZE + TILE_SIZE / 2.0f;
			m_position.y = m_nextTile.y * TILE_SIZE + TILE_SIZE / 2.0f;
			m_moving = false;
			m_animTime = 0.0f;
			m_animTile = 3;
		}
		else {
			//calculate players position in path
			glm::vec2 calcPos;
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
		}
	}
}

void Player::init(std::string texturePath, glm::ivec2 tileSheetSize, DPE::InputManager* inputManager, DPE::Camera2D* camera, glm::ivec2 startPos)
{
	m_health = 10;

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
