#include "VisionStuff.h"
#include <iostream>

VisionStuff::VisionStuff()
{
}


VisionStuff::~VisionStuff()
{
}

void VisionStuff::Run() {

	m_map.resize(50);
	for (int i = 0; i < m_map.size(); i++) {
		m_map[i].resize(50);
		for (int b = 0; b < m_map[0].size(); b++) {
			m_map[i][b] = 0;
		}
	}
	
	glm::ivec2 startPos(0, 0);
	glm::ivec2 endPos(10, 4);

	m_map[1][3] = 1;

	drawLine(startPos, endPos);

	m_map[29][31] = 1;

	glm::ivec2 startVision(30);
	//seperate test for player vision
	calculateShadows(startVision);

	//flips map
	for (int y = m_map.size() - 1; y >= 0; y--) {
		for (int x = 0; x < m_map[0].size(); x++) {
			std::cout << m_map[y][x];
		}
		std::cout << "\n";
	}
}

void VisionStuff::drawLine(glm::ivec2 startPos, glm::ivec2 endPos)
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
		if (m_map[y * signOfY + startPos.y][x * signOfX + startPos.x] != 1) {
			m_map[y * signOfY + startPos.y][x * signOfX + startPos.x] = 2;
			error += slope;
			while (error >= 0.5 && y <= abs(deltaY)) {
				y = y + 1;
				error = error - 1.0f;
				if (m_map[y * signOfY + startPos.y][x * signOfX + startPos.x] != 1) {
					m_map[y * signOfY + startPos.y][x * signOfX + startPos.x] = 2;
				}else {
					m_map[y + startPos.y][x + startPos.x] = 3;
					break;
				}
			}
		}
		else {
			m_map[y + startPos.y][x + startPos.x] = 3;
			break;
		}

	}
}

void VisionStuff::calculateShadows(glm::ivec2 startPos)
{
	//o represents current octant
	for (int o = 0; o < 8; o++) {
		int y = VIEW_DISTANCE;
		for (int x = 0; x <= VIEW_DISTANCE; x++) {
			glm::ivec2 pos = getOctantPosFromGlobal(y, x, o);
			pos.x += startPos.x;
			pos.y += startPos.y;
			drawLine(startPos, pos);
		}
	}

	//debug crap
	m_map[startPos.y][startPos.x] = 4;
	m_map[20][20] = 5;

}

glm::ivec2 VisionStuff::getOctantPosFromGlobal(int row, int col, int octant)
{
	//Split the 360 degrees round the player with 45 degree 'octants'
	//takes position relative to player
	switch (octant) {
	case 0: return glm::ivec2(col, row);
	case 1: return glm::ivec2(row, col);
	case 2: return glm::ivec2(row, -col);
	case 3: return glm::ivec2(col, -row);
	case 4: return glm::ivec2(-col, row);
	case 5: return glm::ivec2(-row, col);
	case 6: return glm::ivec2(-row, -col);
	case 7: return glm::ivec2(-col, -row);
	}
}
