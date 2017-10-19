#include "DungeonGenerator.h"

#include <random>
#include <ctime>
#include <iostream>

DungeonGenerator::DungeonGenerator()
{
}


DungeonGenerator::~DungeonGenerator()
{
}

void DungeonGenerator::Run()
{
	//allocate the vectors
	int rows = 100;
	int columns = 100;

	//reserve the map 
	m_map.resize(rows);

	for (int r = 0; r < rows; r++)
		m_map[r].resize(columns, 1);

	//rooms first
	generateRooms(rows, columns);

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			std::cout << m_map[r][c];
		}
		std::cout<<"\n";
	}

}

void DungeonGenerator::generatePerfMaze()
{
}

void DungeonGenerator::generateRooms(int rows, int columns)
{
	//min and max in space for length always will be even
	int minLength = 4;
	int maxLength = 10;

	//store as type Room to use a room enum later
	std::vector<Room> rooms;

	//atempts to make a room
	//will be the max area divide by the maxArea and should be have of total space
	int attempts = rows * columns / 2;
	std::cout << "Populating with rooms at "<<attempts<<" attempts before termination." << std::endl;

	for (int i = 0; i < attempts; i++) {
		Room room;
		
		glm::vec4 destRect;

		//length
		destRect.z = randInt(minLength, maxLength);
		//height
		destRect.w = randInt(minLength, maxLength);
		
		destRect.x = randInt(1, columns - 2);
		destRect.y = randInt(1, rows - 2);

		room.destRect = destRect;
		
		if (checkRoomCollisions(room, rooms, rows, columns)) {
			//add rooms to map
			rooms.push_back(room);

			//Add it to the maze
			for (int r = 0; r < room.destRect.w; r++) {
				for (int c = 0; c < room.destRect.z; c++) {
					//height and than width
					m_map[r + room.destRect.y - 1][c + room.destRect.x - 1] = 0;
				}
			}
		}
	}
}

void DungeonGenerator::joinSomeDeadEnds()
{
}

bool DungeonGenerator::checkRoomCollisions(const Room & room, std::vector<Room> rooms, int rows, int columns)
{
	//check if out of map
	if (room.destRect.x + room.destRect.z > columns ||
		room.destRect.y + room.destRect.w > rows)
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
