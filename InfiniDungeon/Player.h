#pragma once

#include <DPE/InputManager.h>
#include <DPE/Camera2D.h>

#include "Creature.h"

class Player : public Creature
{
public:
	Player();
	~Player();

	virtual void update(float deltaTime, std::vector<std::vector<int>> level)override;

	void init(std::string texturePath, glm::ivec2 tileSheetSize, DPE::InputManager* inputManager, DPE::Camera2D* camera,float speed);

private:
	DPE::InputManager* m_inputManager;
	DPE::Camera2D* m_camera;

	float m_animTime = 0.0f;

	bool m_wasMouseDownPreviously = false;
};

