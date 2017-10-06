#pragma once

#include "Node.h"

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


class PathFinder
{
public:
	PathFinder();
	~PathFinder();

	std::vector<Node> pathBetweenPoints(const glm::vec2& start, const glm::vec2& end);

private:
	void printPath(std::unordered_map<glm::ivec2, Node, KeyFuncs, KeyFuncs>& nodeMap);

	Node calculatePath(std::unordered_map<glm::ivec2, Node, KeyFuncs, KeyFuncs>& nodeMap, const glm::vec2 & start, const glm::vec2 & finish);

	int bestScore(std::vector<Node>& nodeMap, const glm::vec2& goal);

	void getLocalNodes(std::vector<Node> &openNodes, std::unordered_map<glm::ivec2, Node, KeyFuncs, KeyFuncs>& nodeMap, const Node &start);

	bool isPositionValid(const std::unordered_map<glm::ivec2, Node, KeyFuncs, KeyFuncs>& nodeMap, const Node& myNode);

	std::vector<std::string> m_maze;

	int m_counter;
};

