#include "App.h"
#include <DPE/ScreenList.h>

App::App()
{
}


App::~App()
{

}

void App::onInit() {
}

void App::addScreens() {
	m_initGameScreen = std::make_unique<InitGameScreen>(&m_window);
	m_gameplayScreen = std::make_unique<GameplayScreen>(&m_window);

	m_screenList->addScreen(m_initGameScreen.get());
	m_screenList->addScreen(m_gameplayScreen.get());

	m_screenList->setScreen(m_initGameScreen->getScreenIndex());
}

void App::onExit() {
}
