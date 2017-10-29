#pragma once
#include <string>

struct theme {
	theme() {};

	theme(std::string name, std::string floor, std::string wall) :
		name(name),
		floor(floor),
		wall(wall) {};

	std::string name;
	std::string floor;
	std::string wall;
	//std::string door;
};

const theme levelOne[] = {
	//basic
	theme("Basic","Floor.png","Wall.png")};