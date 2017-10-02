#pragma once

#include <DPE/IMaingame.h>

#include "InitGameScreen.h"
#include "GameplayScreen.h"

class App : public DPE::IMainGame
{
public:
	App();
	~App();

	virtual void onInit() override;
	virtual void addScreens() override;
	virtual void onExit() override;
private:
	std::unique_ptr<InitGameScreen> m_initGameScreen = nullptr;
	std::unique_ptr<GameplayScreen> m_gameplayScreen = nullptr;
};

