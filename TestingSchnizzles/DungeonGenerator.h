#pragma once
class DungeonGenerator
{
public:
	DungeonGenerator();
	~DungeonGenerator();


	//We will be generating a dungeon with this simple algorithm
	//Create a perfect maze tha never intersects with other corridors
	//Fill some of the dead ends recursively
	//Add Rooms in areas with plenty of space(preferabbly at what is left of dead ends)
	//Those rooms will be given different generators later
	//Add a start room and an altar room

	void Run();
};

