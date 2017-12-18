#pragma once
#include <DPE/IGameScreen.h>
#include <DPE/Window.h>
#include <DPE/DebugRender.h>
#include <DPE/Camera2D.h>
#include <DPE/GLTexture.h>
#include <DPE/SpriteBatch.h>

#include "Level.h"

#include "BadGuy.h"
#include "Player.h"
#include "Themes.h"

class GameplayScreen : public DPE::IGameScreen
{
public:
	GameplayScreen(DPE::Window* window);
	~GameplayScreen();

	// Inherited via IGameScreen
	virtual int getNextScreenIndex() const override;

	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;

	virtual void destroy() override;

	virtual void onEntry() override;

	virtual void onExit() override;

	virtual void update() override;

	virtual void draw() override;
	
	//commands
	int getCreatures(std::vector<std::string> args);
	int getCreatureStats(std::vector<std::string> args);
	int testDamage(std::vector<std::string> args);
	int testDamageDefend(std::vector<std::string> args);
	int testDamageAttack(std::vector<std::string> args);

private:

	void updateDamage();

	void checkInput();

	DPE::SpriteBatch m_spriteBatch;
	DPE::GLSLProgram m_textureProgram;
	DPE::Camera2D m_camera;
	DPE::GLTexture m_texture;
	DPE::Window* m_window;
	DPE::DebugRender m_debugRender;

	Level m_level;

	Player m_player;
	std::vector<BadGuy*> m_badGuys;

	float m_prevTicks;

	float m_scrollLevel;
	int m_difficulty;
};