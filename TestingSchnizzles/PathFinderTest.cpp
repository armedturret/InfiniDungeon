#include "PathFinderTest.h"
#include <iostream>


PathFinderTest::PathFinderTest()
{
}


PathFinderTest::~PathFinderTest()
{
}

void PathFinderTest::Run()
{
	//for the first attempt, I will be making the A* algorithim
	//0 is start and G is goal
	m_maze.push_back("XXXXXXXXXX");
	m_maze.push_back("X________X");
	m_maze.push_back("X0_______X");
	m_maze.push_back("X________X");
	m_maze.push_back("X________X");
	m_maze.push_back("X________X");
	m_maze.push_back("X________X");
	m_maze.push_back("X_____G__X");
	m_maze.push_back("X________X");
	m_maze.push_back("XXXXXXXXXX");

	glm::vec2 start;
	glm::vec2 finish;

	for (int r = 0; r < m_maze.size(); r++) {
		for (std::string::size_type c = 0; c < m_maze[r].length(); c++) {
			if (m_maze[r][c] == '0') {
				start = glm::vec2((float)r, (float)c);
			}
			else if (m_maze[r][c] == 'G') {
				finish = glm::vec2((float)r, (float)c);
			}
		}
	}

	std::cout << start.x << " " << start.y << " " << finish.x << " " << finish.y << " " << std::endl;
}
