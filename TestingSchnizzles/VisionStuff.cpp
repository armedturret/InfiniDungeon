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

	float slope = deltaY / deltaX;

	//errpr calculation for Bresenham algorithm
	//when greater than 0.5, line incremented by one so y value must increase
	float error = slope - 0.5;

	int y = 0;

	//cancel if solid

	for (int x = 0; x <= deltaX; x++) {
		if (m_map[y + startPos.y][x + startPos.x] != 1) {
			m_map[y + startPos.y][x + startPos.x] = 2;
			error += slope;
			while (error >= 0.5) {
				y = y + 1;
				error = error - 1.0f;
			}
		}
		else {
			m_map[y + startPos.y][x + startPos.x] = 5;
			break;
		}
	}

	m_map[startPos.y][startPos.x] = 3;
	m_map[endPos.y][endPos.x] = 4;
}

void VisionStuff::calculateShadows(glm::ivec2 startPos)
{
	//Step 1: Split the 360 degrees round the player with 45 degree 'octants'
}
