#pragma once

#include <DPE\SpriteBatch.h>
#include <DPE\DebugRender.h>
#include <DPE\GLSLProgram.h>
#include <vector>

const int TILE_SIZE = 128;

class Level
{
public:
	Level();
	~Level();

	void init(int difficulty);

	void draw(glm::mat4& projectionMatrix, DPE::GLSLProgram & program);

	void dispose();

	std::vector<std::vector<int>> getMap() const { return m_map; };

private:

	DPE::SpriteBatch m_spriteBatch;
	DPE::DebugRender m_debugRenderer;

	std::vector<std::vector<int>> m_map;

	std::string m_theme;
};

