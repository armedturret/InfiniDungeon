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
		//TODO: Remove json code due to being dumb
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

	int rows = 100;
	int columns = 100;

	//reserve the map 
	m_map.resize(rows);

	for (int r = 0; r < rows; r++)
		m_map[r].resize(columns, 1);

	//!!IMPORTANT all spacing must be in multiples of 2 because spacing

	//rooms first
	generateRooms(rows, columns);

	//Populate with corridors
	generatePerfMaze();
	
	m_spriteBatch.init();

	m_debugRenderer.init();

	m_spriteBatch.begin();
	for (int x = 0; x < rows; x++) {
		for (int y = 0; y < columns; y++) {
			glm::vec4 destRect;
			destRect.x = x*TILE_SIZE;
			destRect.y = y*TILE_SIZE;
			destRect.z = TILE_SIZE;
			destRect.w = TILE_SIZE;
			float angle = 0.0f;
			std::string texture;
			if (m_map[y][x] == 0) {
				texture = "Data/Textures/Themes/" + m_theme + "/Floor.png";
			}
			else if (m_map[y][x] == 1) {
				texture = "Data/Textures/Themes/" + m_theme + "/Wall.png";
			}

			m_spriteBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), DPE::ResourceManager::getTexture(texture).id, 0.0f, DPE::ColorRGBA8(255, 255, 255, 255), angle);
		}
	}
	m_spriteBatch.end();
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

void Level::generatePerfMaze()
{
	std::cout << "Generating perfect maze" << std::endl;
	glm::ivec2 currentNode = glm::ivec2(2);
	std::vector<glm::ivec2> openList;

	openList.push_back(currentNode);
	while (openList.size() > 0) {
		m_map[currentNode.y][currentNode.x] = 0;
		std::vector<glm::ivec2> localTiles;
		getAdjacentTiles(openList[openList.size() - 1], localTiles);

		if (localTiles.size() == 0) {
			openList.erase(openList.begin() + openList.size() - 1);
		}
		else {
			int dir = (randInt(0, (localTiles.size() / 2) - 1) * 2);
			//set current tile
			currentNode.x = localTiles[dir].x;
			currentNode.y = localTiles[dir].y;

			//create inbetween tile
			m_map[localTiles[dir + 1].y][localTiles[dir + 1].x] = 0;
			openList.push_back(currentNode);

		}
		localTiles.clear();

	}
}

void Level::generateRooms(int rows, int columns)
{
	//min and max in space for length always will be even
	int minLength = 2;
	int maxLength = 5;

	//store as type Room to use a room enum later
	std::vector<Room> rooms;

	//atempts to make a room
	//will be the max area divide by the maxArea and should be have of total space
	int attempts = rows * columns / (minLength*minLength) / 4;
	std::cout << "Populating with rooms at " << attempts << " attempts before termination." << std::endl;

	for (int i = 0; i < attempts; i++) {
		Room room;

		glm::vec4 destRect;

		//length
		destRect.z = randInt(minLength, maxLength) * 2;
		//height
		destRect.w = randInt(minLength, maxLength) * 2;

		destRect.x = randInt(2, (columns - 2) / 2) * 2;
		destRect.y = randInt(2, (rows - 2) / 2) * 2;

		room.destRect = destRect;

		if (checkRoomCollisions(room, rooms, rows, columns)) {
			//add rooms to map
			rooms.push_back(room);

			//Add it to the maze
			for (int r = 0; r < room.destRect.w; r++) {
				for (int c = 0; c < room.destRect.z; c++) {
					//height and than width
					m_map[r + room.destRect.y][c + room.destRect.x] = 0;
				}
			}
		}
	}
}

void Level::getAdjacentTiles(const glm::ivec2 & startNode, std::vector<glm::ivec2>& output)
{
	//up
	glm::vec2 temp;
	glm::vec2 midTemp;
	temp.x = startNode.x;
	temp.y = startNode.y - 2;
	//tile to reach the next one
	midTemp.x = startNode.x;
	midTemp.y = startNode.y - 1;
	if (isTileValid(temp)) {
		output.push_back(temp);
		output.push_back(midTemp);
	}

	//down
	temp.x = startNode.x;
	temp.y = startNode.y + 2;
	//tile to reach the next one
	midTemp.x = startNode.x;
	midTemp.y = startNode.y + 1;
	if (isTileValid(temp)) {
		output.push_back(temp);
		output.push_back(midTemp);
	}

	//left
	temp.x = startNode.x - 2;
	temp.y = startNode.y;
	//tile to reach the next one
	midTemp.x = startNode.x - 1;
	midTemp.y = startNode.y;
	if (isTileValid(temp)) {
		output.push_back(temp);
		output.push_back(midTemp);
	}

	//right
	temp.x = startNode.x + 2;
	temp.y = startNode.y;
	//tile to reach the next one
	midTemp.x = startNode.x + 1;
	midTemp.y = startNode.y;
	if (isTileValid(temp)) {
		output.push_back(temp);
		output.push_back(midTemp);
	}
}

bool Level::isTileValid(glm::ivec2 checkTile)
{
	//check if out of map
	if (m_map.size() >= checkTile.x + 1 &&
		0 < checkTile.x - 1 &&
		m_map[0].size() >= checkTile.y + 1 &&
		0 < checkTile.y - 1)

		//right, left, up, down
		if (m_map[checkTile.y + 1][checkTile.x] == 1 &&
			m_map[checkTile.y - 1][checkTile.x] == 1 &&
			m_map[checkTile.y][checkTile.x - 1] == 1 &&
			m_map[checkTile.y][checkTile.x + 1] == 1)
			return true;

	return false;
}

void Level::joinSomeDeadEnds()
{
}

bool Level::checkRoomCollisions(const Room & room, std::vector<Room> rooms, int rows, int columns)
{
	//check if out of map
	if (room.destRect.x + room.destRect.z > columns - 1 ||
		room.destRect.y + room.destRect.w > rows - 1)
		return false;

	for (int b = 0; b < rooms.size(); b++/*the equivelant of an A- XD*/) {
		if (doesRoomCollide(room, rooms[b])) {
			return false;
		}
	}

	return true;
}

bool Level::doesRoomCollide(const Room & room1, const Room & room2)
{
	glm::vec4 rect1 = room1.destRect;
	glm::vec4 rect2 = room2.destRect;

	//AABB collision
	if (rect1.x - 1 < rect2.x + rect2.z + 1 &&
		rect1.x + rect1.z + 1 > rect2.x - 1 &&
		rect1.y - 1< rect2.y + rect2.w + 1 &&
		rect1.w + rect1.y + 1 > rect2.y - 1) {
		return true;
	}
	return false;
}

int Level::randInt(int min, int max)
{
	//improved version of rand() from <random>
	static std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int> randInteger(min, max);

	return randInteger(randomEngine);
}

float Level::randFloat(float min, float max)
{
	//improved version of rand() from <random>
	static std::mt19937 randomEngine(time(nullptr));
	std::uniform_real_distribution<float> randomFloat(min, max);

	return randomFloat(randomEngine);
}