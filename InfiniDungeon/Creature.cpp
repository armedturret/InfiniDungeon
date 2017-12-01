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

void Creature::applyDamage(const int & damage)
{
	//that's a lot of damage
	m_health -= damage;

	//check if over max health
	if (m_health > m_maxHealth)
		m_health = m_maxHealth;
}

bool Creature::moveToNextTile(std::vector<Node>& path, const std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& entmap, float deltaTime)
{	
	//increment animTime
	m_animTime += deltaTime;

	//the position prior to the move
	glm::vec2 calcPos;

	if (floor(m_animTime) < path.size()) {
		calcPos.x = path[floor(m_animTime)].getPosition().x * TILE_SIZE + TILE_SIZE / 2;
		calcPos.y = path[floor(m_animTime)].getPosition().y * TILE_SIZE + TILE_SIZE / 2;
	}

	//close/open door if needed
	if (floor(m_animTime) - 1 > -1) {
		glm::vec2 prevPos = path[floor(m_animTime) - 1].getPosition();
		//check if tile door
		if(map[prevPos.y][prevPos.x] == 2)
			entmap[prevPos.y][prevPos.x] = 0;

		glm::vec2 currentPos = path[floor(m_animTime)].getPosition();
		//check if tile door
		if (map[currentPos.y][currentPos.x] == 2)
			entmap[currentPos.y][currentPos.x] = 1;
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
		
		//reset animation
		m_animTime = 0.0;
		m_animTile = 0;
		return true;
	}

	//calculate which direction to face
	if (m_nextPosition.x < calcPos.x) {
		//left
		m_direction = 2;
	}
	else if (m_nextPosition.x > calcPos.x) {
		//right
		m_direction = 1;
	}

	//the time into the current movement
	double currentTileTime = m_animTime - floor(m_animTime);

	//calculate movement gradient if not intermediate
	if (Random::equals(m_animTime, floor(m_animTime))&&deltaTime>0.0f) {
		m_position.x = calcPos.x;
		m_position.y = calcPos.y;
		return true;
	}
	else {
		//difference between current tile and next pos
		glm::vec2 difference;
		
		difference.x = m_nextPosition.x - calcPos.x;
		difference.y = m_nextPosition.y - calcPos.y;

		// add the multiply difference by currentTileTime
		calcPos.x += difference.x * currentTileTime;
		calcPos.y += difference.y * currentTileTime;

		m_position.x = calcPos.x;
		m_position.y = calcPos.y;
	}
	
	//calculate which fram the character is at
	//also check if its animating
	if ((int)(currentTileTime * 10) % (int)m_animSpeed == 0 && !Random::equals(deltaTime, 0.0))
		m_animTile += 1;
	else if (Random::equals(deltaTime, 0.0))
		m_animTile = 0;

	if (m_animTile > 2)
		m_animTile = 0;

	return false;
}

bool Creature::seesPoint(const std::vector<std::vector<int>>& map, const std::vector<std::vector<int>>& entmap, glm::vec2 end)
{
	//calculate creatureslocation
	glm::ivec2 currentPos;
	currentPos.x = std::round((m_position.x - TILE_SIZE / 2.0f) / TILE_SIZE);
	currentPos.y = std::round((m_position.y - TILE_SIZE / 2.0f) / TILE_SIZE);

	glm::ivec2 goal;
	goal.x = std::round((end.x - TILE_SIZE / 2.0f) / TILE_SIZE);
	goal.y = std::round((end.y - TILE_SIZE / 2.0f) / TILE_SIZE);

	return visionThing.canSeePoint(map, entmap, currentPos, goal);
}
