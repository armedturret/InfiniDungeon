#pragma once

#include <DPE/InputManager.h>
#include <DPE/Window.h>

#include "Creature.h"

class Player : public Creature
{
public:
	Player();
	~Player();

	virtual void update(float deltaTime)override;

	void init(std::string texturePath, glm::ivec2 tileSheetSize, DPE::InputManager* inputManager, DPE::Window* window,float speed);

private:
	DPE::InputManager* m_inputManager;
	DPE::Window* m_window;
};

