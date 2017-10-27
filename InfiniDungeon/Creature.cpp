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
	/*float animSpeed = 0.1f;

	if (m_direction == 0) {
		animTile = 0;
	}else if (m_direction == 1) {
		animTile = 3;
	}else if (m_direction == 2) {
		animTile = 0;
	}else
	if (m_direction == 3) {
		animTile = 6;
	}

	m_animTime += animSpeed;
	if(moving)
		animTile = animTile + 1 + (int)m_animTime % 2;
	*/

	glm::vec4 uvRect = m_tileSheet.getUVs(m_animTile);

	if (m_direction == 2) {
		uvRect.x += 1.0f / m_tileSheet.dims.x;
		uvRect.z *= -1;
	}

	m_spriteBatch.draw(glm::vec4(m_position.x-TILE_SIZE/2.0f, m_position.y - TILE_SIZE / 2.0f, TILE_SIZE, TILE_SIZE), uvRect, m_tileSheet.texture.id, 0.0f, DPE::ColorRGBA8(255, 255, 255, 255));
}
