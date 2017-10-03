#include "Player.h"

#include <DPE/ResourceManager.h>


Player::Player()
{
}


Player::~Player()
{
}

void Player::update(float deltaTime)
{
	m_position = glm::vec2(128.0f / 2.0f);

	if (m_inputManager->isKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords = m_inputManager->getMouseCoords();
		m_inputManager->
	}
}

void Player::init(std::string texturePath, glm::ivec2 tileSheetSize, DPE::InputManager* inputManager, float speed)
{
	m_speed = speed;

	DPE::GLTexture m_texture = DPE::ResourceManager::getTexture(texturePath);
	m_tileSheet.init(m_texture, tileSheetSize);

	m_inputManager = inputManager;

}