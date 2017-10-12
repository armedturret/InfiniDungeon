#include "DungeonGenerator.h"

#include <random>
#include <ctime>

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

	for (int r = 100; r < rows; r++)
		m_map[r].resize(columns);

	//rooms first
	generateRooms(rows * columns);

}

void DungeonGenerator::generatePerfMaze()
{
}

void DungeonGenerator::generateRooms(int rowsTimesColumns)
{
	//min and max in space for length always will be even
	int minLength = 4;
	int maxLength = 10;

	//atempts to make a room
	//will be the max area divide by the maxArea and should be have of total space
	int attempts = rowsTimesColumns / (maxLength * 2) / 2;

}

void DungeonGenerator::joinSomeDeadEnds()
{
}

int DungeonGenerator::randInt(int min, int max)
{
	//improved version of rand() from <random>
	static std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int> randInteger(min, max);

	return randInteger(randomEngine);
}