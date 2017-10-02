#pragma once

#include <DPE/IGameScreen.h>
#include <DPE/SpriteBatch.h>
#include <DPE/GLSLProgram.h>
#include <DPE/Camera2D.h>
#include <DPE/Window.h>
#include <DPE/GLTexture.h>
#include <DPE/DebugRender.h>

#include "PreAllocate.h"

class InitGameScreen : public DPE::IGameScreen
{
public:
	InitGameScreen(DPE::Window* window);
	~InitGameScreen();

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

	DPE::Camera2D m_camera;
	DPE::Window* m_window;
	DPE::GLTexture m_texture;
	DPE::SpriteBatch m_spriteBatch;
	DPE::GLSLProgram m_textureProgram;
	
	PreAllocate m_preAllocate;

	float m_animTime = 0.0f;
};

