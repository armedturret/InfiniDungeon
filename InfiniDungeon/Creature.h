#pragma once
#include <DPE/TileSheet.h>
#include <DPE/SpriteBatch.h>
#include <DPE/DebugRender.h>
#include <iostream>

class Creature
{
public:
	Creature();
	~Creature();
	virtual void update(float deltaTime, const std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& entMap) {
		std::cout << "Creature given no update behavior" << std::endl;
	};

	void draw(DPE::SpriteBatch& m_spriteBatch);

	glm::vec2 getPosition() const { return m_position; }

	const int TILE_SIZE = 128;

private:
	float m_animTime = 0;

protected:
	int randInt(int min, int max);

	float randFloat(float min, float max);

	glm::vec2 m_position = glm::vec2(0.0f, 0.0f);
	int m_direction = 0; // 0 = left, 1 = up, 2 = right, 3 = down

	DPE::TileSheet m_tileSheet;
	DPE::ColorRGBA8 m_color;

	int m_health = 10;

	bool moving = false;

	int m_animTile = 0;
};

