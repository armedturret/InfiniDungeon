#pragma once
#include <string>

#include "BadGuy.h"

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

	BadGuy levelOneEnemy;
};

const theme LEVEL_ONE[] = { theme("Basic", "Floor.png", "Wall.png", "Door.png") };