#pragma once

#include <DPE/InputManager.h>
#include <DPE/Camera2D.h>

#include "PathFinder.h"
#include "Creature.h"

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
	DPE::InputManager* m_inputManager;
	DPE::Camera2D* m_camera;

	PathFinder m_pathFinder;

	std::vector<Node> m_path;

	glm::vec2 m_target;

	//double somehow fixes glitches
	double m_animTime = 0.0;

	bool m_wasMouseDownPreviously = false;

	bool m_wasLDownPreviously = false;

	bool m_moving = false;

	glm::vec2 m_startPosition;

	glm::vec2 m_nextTile;
};

