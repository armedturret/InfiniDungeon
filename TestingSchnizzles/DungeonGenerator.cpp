#include "DungeonGenerator.h"

#include <random>
#include <ctime>
#include <iostream>
#include <unordered_map>

DungeonGenerator::DungeonGenerator()
{
}


DungeonGenerator::~DungeonGenerator()
{
}

void DungeonGenerator::Run()
{
	//allocate the vectors
	int rows = 50;
	int columns = 50;

	//reserve the map 
	m_map.resize(rows);

	for (int r = 0; r < rows; r++)
		m_map[r].resize(columns, 1);

	//!!IMPORTANT all spacing must be in multiples of 2 because spacing

	//rooms first
	generateRooms(rows, columns);

	//Populate with corridors
	generatePerfMaze();

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			std::cout << m_map[r][c];
		}
		std::cout<<"\n";
	}

}

void DungeonGenerator::generatePerfMaze()
{
	std::cout << "Generating perfect maze" << std::endl;
	glm::ivec2 currentNode = glm::ivec2(2);
	std::vector<glm::ivec2> openList;
	
	openList.push_back(currentNode);
	while (openList.size() > 0) {
		m_map[currentNode.y][currentNode.x] = 0;
		std::vector<glm::ivec2> localTiles;
		getAdjacentTiles(openList[openList.size()-1], localTiles);

		if (localTiles.size() == 0) {
			std::cout << "deleted" << std::endl;
			openList.erase(openList.begin()+ openList.size() - 1);
		}
		else {
			int dir = (randInt(0, (localTiles.size()/2) -1) * 2);
			//set current tile
			currentNode.x = localTiles[dir].x;
			currentNode.y = localTiles[dir].y;

			//create inbetween tile
			m_map[localTiles[dir+1].y][localTiles[dir+1].x] = 0;
			openList.push_back(currentNode);
			
		}
		localTiles.clear();

	}
}

void DungeonGenerator::generateRooms(int rows, int columns)
{
	//min and max in space for length always will be even
	int minLength = 2;
	int maxLength = 5;

	//store as type Room to use a room enum later
	std::vector<Room> rooms;

	//atempts to make a room
	//will be the max area divide by the maxArea and should be have of total space
	int attempts = rows * columns / (minLength*minLength) /4;
	std::cout << "Populating with rooms at "<<attempts<<" attempts before termination." << std::endl;

	for (int i = 0; i < attempts; i++) {
		Room room;
		
		glm::vec4 destRect;

		//length
		destRect.z = randInt(minLength, maxLength) * 2;
		//height
		destRect.w = randInt(minLength, maxLength) * 2;
		
		destRect.x = randInt(2, (columns - 2)/2) * 2;
		destRect.y = randInt(2, (rows - 2)/2) * 2;

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

void DungeonGenerator::getAdjacentTiles(const glm::ivec2 & startNode, std::vector<glm::ivec2>& output)
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

	std::cout << "Output: " << output.size() <<" of "<<startNode.x<<" "<<startNode.y<< std::endl;

}

bool DungeonGenerator::isTileValid(glm::ivec2 checkTile)
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

void DungeonGenerator::joinSomeDeadEnds()
{
}

bool DungeonGenerator::checkRoomCollisions(const Room & room, std::vector<Room> rooms, int rows, int columns)
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

bool DungeonGenerator::doesRoomCollide(const Room & room1, const Room & room2)
{
	glm::vec4 rect1 = room1.destRect;
	glm::vec4 rect2 = room2.destRect;

	//AABB collision
	if (rect1.x - 1 < rect2.x + rect2.z + 1 &&
		rect1.x + rect1.z + 1 > rect2.x-1 &&
		rect1.y - 1< rect2.y + rect2.w + 1 &&
		rect1.w + rect1.y + 1 > rect2.y - 1) {
		return true;
	}
	return false;
}

int DungeonGenerator::randInt(int min, int max)
{
	//improved version of rand() from <random>
	static std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int> randInteger(min, max);

	return randInteger(randomEngine);
}

float DungeonGenerator::randFloat(float min, float max)
{
	//improved version of rand() from <random>
	static std::mt19937 randomEngine(time(nullptr));
	std::uniform_real_distribution<float> randomFloat(min, max);

	return randomFloat(randomEngine);
}
