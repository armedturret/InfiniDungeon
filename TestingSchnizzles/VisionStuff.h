#pragma once
#include <vector>

#include <glm/glm.hpp>

//how far should the algorithm calculate
const int VIEW_DISTANCE = 10;

class VisionStuff
{
public:
	VisionStuff();
	~VisionStuff();

	void Run();

private:
	void drawLine(glm::ivec2 startPos, glm::ivec2 endPos);

	void calculateShadows(glm::ivec2 startPos);

	glm::ivec2 getOctantPosFromGlobal(int row, int col, int octant);

	std::vector<std::vector<int>> m_map;
};

