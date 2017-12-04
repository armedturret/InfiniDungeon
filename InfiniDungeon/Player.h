#pragma once

#include <DPE/InputManager.h>
#include <DPE/Camera2D.h>

#include "Creature.h"

const double MAX_COMBAT_TILES = 6.0;

class Player : public Creature
{
public:
	Player();
	~Player();

	virtual void update(float deltaTime,
		const std::vector<std::vector<int>>& map,
		std::vector<std::vector<int>>& entMap,
		std::vector<BadGuy*>& badGuys,
		Player& jeff)override;

	void init(std::string texturePath, glm::ivec2 tileSheetSize, DPE::InputManager* inputManager, DPE::Camera2D* camera, glm::ivec2 startPos);

	float getDeltaFactor();

private:
	bool seesEnemy(std::vector<BadGuy*> badGuys, const std::vector<std::vector<int>>& map, const std::vector<std::vector<int>>& entmap);

	DPE::InputManager* m_inputManager;
	DPE::Camera2D* m_camera;

	std::vector<Node> m_path;

	glm::vec2 m_target;

	bool m_waiting = false;
	bool m_moving = false;

	glm::vec2 m_startPosition;

	glm::vec2 m_nextTile;

	bool m_enemiesSpotted = false;
};

