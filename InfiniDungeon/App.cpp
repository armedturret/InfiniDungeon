#include "App.h"
#include <DPE/ScreenList.h>

App::App()
{
}


App::~App()
{

}

void App::onInit() {
	gameConsole.init();
}

void App::addScreens() {
	m_initGameScreen = std::make_shared<InitGameScreen>(&m_window);
	m_gameplayScreen = std::make_shared<GameplayScreen>(&m_window);

	m_screenList->addScreen(m_initGameScreen.get());
	m_screenList->addScreen(m_gameplayScreen.get());

	m_screenList->setScreen(m_initGameScreen->getScreenIndex());

	gameConsole.run(m_gameplayScreen);
}

void App::onExit() {
	gameConsole.destroy();
}
