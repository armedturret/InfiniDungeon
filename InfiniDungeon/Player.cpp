#include "Player.h"

#include <DPE/ResourceManager.h>


Player::Player():m_target(0.0f)
{
}


Player::~Player()
{
}

void Player::update(float deltaTime, std::vector<std::vector<int>> level)
{
	if (m_inputManager->isKeyDown(SDL_BUTTON_LEFT) && !m_wasMouseDownPreviously) {
		if (!m_moving) {
			glm::vec2 worldCoords = m_camera->convertScreenToWorld(m_inputManager->getMouseCoords());
			m_target.x = floor(worldCoords.x / TILE_SIZE);
			m_target.y = floor(worldCoords.y / TILE_SIZE);

			//Test if coordinates are in map
			if (m_target.x >= 0.0f && m_target.y >= 0.0f && m_target.x < level.size() && m_target.y < level[0].size()) {
				std::cout << m_target.x << " " << m_target.y << std::endl;
				m_moving = true;
				
				glm::vec2 startPosition;
				startPosition.x = (m_position.x - TILE_SIZE / 2.0f) / TILE_SIZE;
				startPosition.y = (m_position.y - TILE_SIZE / 2.0f) / TILE_SIZE;

				m_path = m_pathFinder.pathBetweenPoints(startPosition, m_target, level);
			}
		}
		else {
			m_moving = false;
		}
		//custom "press" rejection because the engine is buggy
		m_wasMouseDownPreviously = true;
	}
	else if(!m_inputManager->isKeyDown(SDL_BUTTON_LEFT)) {
		m_wasMouseDownPreviously = false;
	}
	if (m_moving) {
		glm::vec2 calcPos;
		if (m_animTime < m_path.size()) {
			calcPos = m_path[m_path.size() - floor(m_animTime) - 1].getPosition();
			m_position.x = calcPos.x * TILE_SIZE + TILE_SIZE / 2.0f;
			m_position.y = calcPos.y * TILE_SIZE + TILE_SIZE / 2.0f;

			std::cout << m_animTime << std::endl;
			m_animTime += 0.1f;
		}
		else {
			m_moving = false;
			m_animTime = 0.0f;
		}
		
	}
}

void Player::init(std::string texturePath, glm::ivec2 tileSheetSize, DPE::InputManager* inputManager, DPE::Camera2D* camera, float speed)
{
	m_speed = speed;

	DPE::GLTexture m_texture = DPE::ResourceManager::getTexture(texturePath);
	m_tileSheet.init(m_texture, tileSheetSize);

	m_inputManager = inputManager;

	m_camera = camera;

	m_position = glm::vec2(TILE_SIZE / 2.0f);
}