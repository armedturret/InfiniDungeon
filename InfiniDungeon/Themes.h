#pragma once
#include <string>

struct theme {
	theme() {};

	theme(std::string name, std::string floor, std::string wall, std::string door) :
		name(name),
		floor(floor),
		wall(wall),
		door(door){};

	std::string name;
	std::string floor;
	std::string wall;
	std::string door;
};

const theme LEVEL_ONE[] = { theme("Underdark", "Floor.png", "Wall.png", "Door.png") };