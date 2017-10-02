#include "Level.h"

#include <DPE/ResourceManager.h>

Level::Level()
{
}


Level::~Level()
{
}

void Level::init()
{
	int rows = 10;
	int columns = 10;

	
	m_spriteBatch.init();

	m_debugRenderer.init();

	m_spriteBatch.begin();
	for (int x = 0; x < rows; x++) {
		for (int y = 0; y < columns; y++) {
			glm::vec4 destRect;
			destRect.x = x*TILE_SIZE;
			destRect.y = y*TILE_SIZE;
			destRect.z = TILE_SIZE;
			destRect.w = TILE_SIZE;
			float angle = 0.0f;
			std::string texture;
			texture = "Data/Textures/Floor.png";

			m_spriteBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), DPE::ResourceManager::getTexture(texture).id, 0.0f, DPE::ColorRGBA8(255, 255, 255, 255), angle);
			m_debugRenderer.drawBox(destRect, DPE::ColorRGBA8(255, 255, 255, 255), angle);
		}
	}
	m_spriteBatch.end();
	m_debugRenderer.end();
}

void Level::draw(glm::mat4& projectionMatrix, DPE::GLSLProgram & program)
{
	m_spriteBatch.renderBatch();
	m_debugRenderer.render(projectionMatrix, 2.0f);
	program.use();
}

void Level::dispose()
{
	m_spriteBatch.dispose();
	m_debugRenderer.dispose();
}
