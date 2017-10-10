#pragma once

#include <vector>

class DungeonGenerator
{
public:
	DungeonGenerator();
	~DungeonGenerator();


	//We will be generating a dungeon with this simple algorithm
	//Generate all the rooms in the map (Easier than making the maze prior)
	//Create a perfect maze tha never intersects with other corridors to fill in the space
	//Create "connections" between two different regions which is either another room or the maze(Its one region)
	//Repeat until all maze is part of one region
	//Add more "connections" randomly (to do this, make sure all connections are in a list and have a 1 in 50 or 100 chance of opening)
	//Fill all dead ends to make maze sparser

	void Run();

private:
	void generatePerfMaze();

	//TODO: Add some enum for room algorithm
	void generateRooms();

	void joinSomeDeadEnds();

	std::vector<std::vector<int>> m_map;
};

