#include "Player.h"

#include <DPE/ResourceManager.h>


Player::Player()
{
}


Player::~Player()
{
}

void Player::update(float deltaTime, std::vector<std::vector<int>> level)
{
	if (m_inputManager->isKeyDown(SDL_BUTTON_LEFT) && !m_wasMouseDownPreviously) {
		glm::vec2 worldCoords = m_camera->convertScreenToWorld(m_inputManager->getMouseCoords());
		glm::vec2 tileClicked;
		tileClicked.x = floor(worldCoords.x / TILE_SIZE) + 1;
		tileClicked.y = floor(worldCoords.y / TILE_SIZE) + 1;
		
		//Test if coordinates are in map
		if (tileClicked.x > 0.0f && tileClicked.y > 0.0f && tileClicked.x <= level.size() && tileClicked.y <= level[0].size()) {
			std::cout << tileClicked.x << " " << tileClicked.y << std::endl;

			m_position.x = tileClicked.x * TILE_SIZE - TILE_SIZE / 2.0f;
			m_position.y = tileClicked.y * TILE_SIZE - TILE_SIZE / 2.0f;
		}

		//custom "press" rejection because the engine is buggy
		m_wasMouseDownPreviously = true;
	}
	else if(!m_inputManager->isKeyDown(SDL_BUTTON_LEFT)) {
		m_wasMouseDownPreviously = false;
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