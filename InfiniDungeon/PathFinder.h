#pragma once

#include "Node.h"

#include <map>
#include <ctime>

#include <vector>
#include <unordered_map>
#include <string>
#include <glm/glm.hpp>

struct KeyFuncs
{
	size_t operator()(const glm::ivec2& k)const
	{
		return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
	}

	bool operator()(const glm::ivec2& a, const glm:: ivec2& b)const
	{
		return a.x == b.x && a.y == b.y;
	}
};

struct CompareSecond
{
	bool operator()(const std::pair<int, float> left, const std::pair<int, float> right) const
	{
		return left.second < right.second;
	}
};

class PathFinder
{
public:
	PathFinder();
	~PathFinder();

	std::vector<Node> pathBetweenPoints(const glm::vec2& start, const glm::vec2& end, const std::vector<std::vector<int>>& map);

private:
	Node calculatePath(std::unordered_map<glm::ivec2, Node, KeyFuncs, KeyFuncs>& nodeMap, const glm::vec2 & start, const glm::vec2 & finish);

	int bestScore(std::vector<Node>& nodeMap, const glm::vec2& goal, const std::map<int, float>& indexTracker);

	//TODO: Check for open node recursion
	void getLocalNodes(std::vector<Node> &openNodes, std::unordered_map<glm::ivec2, Node, KeyFuncs, KeyFuncs>& nodeMap, const Node &start, const glm::vec2 &goal, std::map<int, float>& indexTracker);

	bool isPositionValid(const std::unordered_map<glm::ivec2, Node, KeyFuncs, KeyFuncs>& nodeMap, const Node& myNode);

	std::vector<std::vector<int>> m_map;

	int m_counter;

	//this is for debug stuff
	std::clock_t m_totalTime;

	std::clock_t m_calculatingBestScore;

	std::clock_t m_calculatingLocalTiles;

	std::clock_t m_reconstructingPath;
};

