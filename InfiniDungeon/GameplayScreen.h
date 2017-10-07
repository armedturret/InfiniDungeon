#pragma once
#include <DPE/IGameScreen.h>
#include <DPE/Window.h>
#include <DPE/DebugRender.h>
#include <DPE/Camera2D.h>
#include <DPE/GLTexture.h>
#include <DPE/SpriteBatch.h>

#include "Level.h"

#include "Player.h"

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

private:

	void checkInput();

	DPE::SpriteBatch m_spriteBatch;
	DPE::GLSLProgram m_textureProgram;
	DPE::Camera2D m_camera;
	DPE::GLTexture m_texture;
	DPE::Window* m_window;
	DPE::DebugRender m_debugRender;

	Level m_level;

	Player m_player;
};
