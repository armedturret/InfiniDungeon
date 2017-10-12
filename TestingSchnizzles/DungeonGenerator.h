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

	//To gen rooms, set an amount of attempts on generation and stop it if the room intersects another

	//Perfect Maze Generation
	//Starting from a random empty cell in the maze, add it to an open list
	//Make a list of all adjacent cells
	//Carve a path to that cell and add it to the open list
	//If their are no empty adjacent cells, remove the current cell from the open list and add it to closed list
	//Just repeat until no cells in the open list

	void Run();

private:
	void generatePerfMaze();

	//TODO: Add some enum for room algorithm
	void generateRooms(int rowsTimesColumns);

	void joinSomeDeadEnds();

	int randInt(int min, int max);

	std::vector<std::vector<int>> m_map;
};

