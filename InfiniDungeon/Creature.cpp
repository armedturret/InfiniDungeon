#include "Creature.h"
#include <DPE/ResourceManager.h>

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
