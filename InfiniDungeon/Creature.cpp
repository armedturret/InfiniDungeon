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

	//get next tile for gradiation between tiles
	if (ceil(m_animTime) < path.size()) {
		m_nextPosition.x = path[ceil(m_animTime)].getPosition().x * TILE_SIZE + TILE_SIZE / 2;
		m_nextPosition.y = path[ceil(m_animTime)].getPosition().y * TILE_SIZE + TILE_SIZE / 2;
	}else {
		//reached end
		path.clear();
		//tecnically an itermiediate
		//set to nextPosition
		m_position.x = m_nextPosition.x;
		m_position.y = m_nextPosition.y;
		return true;
	}

	//calculate movement gradient if not intermediate
	if (m_animTime == (int)m_animTime) {
		m_position.x = calcPos.x;
		m_position.y = calcPos.y;
		return true;
	}
	else {
		//difference between current tile and next pos
		glm::vec2 difference;
		
		difference.x = m_nextPosition.x - calcPos.x;
		difference.y = m_nextPosition.y - calcPos.y;

		//the time into the current movement
		double currentTileTime = m_animTime - floor(m_animTime);

		// add the multiply difference by currentTileTime
		calcPos.x += difference.x * currentTileTime;
		calcPos.y += difference.y * currentTileTime;

		m_position.x = calcPos.x;
		m_position.y = calcPos.y;
	}
	
	

	return false;
}
