#include "BresenhamAlgorithm.h"

#include <iostream>

BresenhamAlgorithm::BresenhamAlgorithm()
{
}


BresenhamAlgorithm::~BresenhamAlgorithm()
{
}

bool BresenhamAlgorithm::canSeePoint(const std::vector<std::vector<int>>& map, glm::ivec2 startPos, glm::ivec2 endPos)
{
	//end pos is the slope at the x of the view distance
	float deltaX = endPos.x - startPos.x;
	float deltaY = endPos.y - startPos.y;

	float slope = abs(deltaY / deltaX);

	//errpr calculation for Bresenham algorithm
	//when greater than 0.5, line incremented by one so y value must increase
	float error = abs(slope) - 0.5;

	int y = 0;

	int signOfX = 1;
	if (deltaX < 0)
		signOfX = -1;

	int signOfY = 1;
	if (deltaY < 0)
		signOfY = -1;

	//check if slope is undefined
	for (int x = 0; x <= abs(deltaX); x++) {
		if (!isTileSolid(map,glm::ivec2(x * signOfX + startPos.x,y * signOfY + startPos.y))) {
			error += slope;
			while (error >= 0.5 && y <= abs(deltaY)) {
				y = y + 1;
				error = error - 1.0f;
				if (map[y * signOfY + startPos.y][x * signOfX + startPos.x] == 1) {
					return false;
				}
			}
		}
		else {
			return false;
		}

	}
	return true;
}

bool BresenhamAlgorithm::isTileSolid(const std::vector<std::vector<int>>& map, const glm::ivec2 & checkPos)
{
	return map[checkPos.y][checkPos.x] == 1 || map[checkPos.y][checkPos.x] == 2;
}
