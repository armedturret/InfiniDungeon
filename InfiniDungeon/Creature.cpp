#include "Creature.h"
#include <DPE/ResourceManager.h>

#include <random>
#include <ctime>

Creature::Creature()
{
}


Creature::~Creature()
{
}

void Creature::draw(DPE::SpriteBatch & m_spriteBatch)
{
	glm::vec4 uvRect = m_tileSheet.getUVs(m_animTile);

	if (m_direction == 2) {
		uvRect.x += 1.0f / m_tileSheet.dims.x;
		uvRect.z *= -1;
	}

	m_spriteBatch.draw(glm::vec4(m_position.x-TILE_SIZE/2.0f, m_position.y - TILE_SIZE / 2.0f, TILE_SIZE, TILE_SIZE), uvRect, m_tileSheet.texture.id, 0.0f, DPE::ColorRGBA8(255, 255, 255, 255));
}

bool Creature::moveToNextTile(std::vector<Node>& path, float deltaTime)
{	
	//increment animTime
	m_animTime += deltaTime;

	//the position prior to the move
	glm::vec2 calcPos;

	if (floor(m_animTime) < path.size()) {
		calcPos.x = path[floor(m_animTime)].getPosition().x * TILE_SIZE + TILE_SIZE / 2;
		calcPos.y = path[floor(m_animTime)].getPosition().y * TILE_SIZE + TILE_SIZE / 2;
	}
	else {
		//reached end
		path.clear();
		return false;
	}

	m_position.x = calcPos.x;
	m_position.y = calcPos.y;

	return false;
}
