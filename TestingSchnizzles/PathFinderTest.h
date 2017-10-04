#pragma once

#include "Node.h"

#include <vector>

class PathFinderTest
{
public:
	PathFinderTest();
	~PathFinderTest();

	void Run();

private:
	std::vector<std::string> m_maze;
};

