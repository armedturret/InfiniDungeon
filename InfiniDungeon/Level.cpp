#include "Level.h"

#include <DPE/ResourceManager.h>

#include <iostream>
#include <fstream>
#include <random>
#include <ctime>

#include <JSON\reader.h>
#include <JSON\value.h>

Level::Level()
{
}


Level::~Level()
{
}

void Level::init(int difficulty)
{
	Json::Value themeSelectRoot;
	
	std::ifstream themes_file("Data/Textures/Themes/Themes.json", std::ios::binary);
	themes_file >> themeSelectRoot;

	//choose a theme of matching difficulty
	if (difficulty == 1) {
		const Json::Value difficultyOne = themeSelectRoot["DifficultyOne"];

		static std::mt19937 randomEngine(time(nullptr));
		std::uniform_int_distribution<int> randInt(0, difficultyOne.size() - 1);
		//choose random theme
		int index = randInt(randomEngine);

		std::cout << difficultyOne[index].asString()<<std::endl;

		m_theme = difficultyOne[index].asString();
	}
	else {
		std::cout << "difficulty not valid" << std::endl;
	}

	int rows = 10;
	int columns = 10;

	
	m_spriteBatch.init();

	m_debugRenderer.init();

	m_spriteBatch.begin();
	for (int x = 0; x < rows; x++) {
		std::vector<int> nestedVector;

		for (int y = 0; y < columns; y++) {
			glm::vec4 destRect;
			destRect.x = x*TILE_SIZE;
			destRect.y = y*TILE_SIZE;
			destRect.z = TILE_SIZE;
			destRect.w = TILE_SIZE;
			float angle = 0.0f;
			std::string texture;
			nestedVector.push_back(0);
			texture = "Data/Textures/Themes/"+m_theme+"/Floor.png";

			m_spriteBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), DPE::ResourceManager::getTexture(texture).id, 0.0f, DPE::ColorRGBA8(255, 255, 255, 255), angle);
			m_debugRenderer.drawBox(destRect, DPE::ColorRGBA8(255, 255, 255, 255), angle);
		}
		m_map.push_back(nestedVector);
		nestedVector.clear();
	}
	m_spriteBatch.end();
	m_debugRenderer.end();
}

void Level::draw(glm::mat4& projectionMatrix, DPE::GLSLProgram & program)
{
	m_spriteBatch.renderBatch();
	m_debugRenderer.render(projectionMatrix, 2.0f);
	program.use();
}

void Level::dispose()
{
	m_spriteBatch.dispose();
	m_debugRenderer.dispose();
}
