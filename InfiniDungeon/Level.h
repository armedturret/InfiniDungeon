#pragma once

#include <DPE\SpriteBatch.h>
#include <DPE\DebugRender.h>
#include <DPE\GLSLProgram.h>

const int TILE_SIZE = 128;

class Level
{
public:
	Level();
	~Level();

	void init();

	void draw(glm::mat4& projectionMatrix, DPE::GLSLProgram & program);

	void dispose();

private:
	DPE::SpriteBatch m_spriteBatch;
	DPE::DebugRender m_debugRenderer;
};

