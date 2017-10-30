#include "PathFinder.h"
#include <iostream>

PathFinder::PathFinder()
{
}


PathFinder::~PathFinder()
{
}

std::vector<Node> PathFinder::pathBetweenPoints(const glm::vec2& start, const glm::vec2& end, const std::vector<std::vector<int>>& map)
{	
	//this list contains the goal node, and which one leads to it
	std::unordered_map<glm::ivec2, Node, KeyFuncs, KeyFuncs> closedNodes;

	m_map = map;

	Node currentNode = calculatePath(closedNodes, start, end);

	std::vector<Node> returnPath;

	std::unordered_map<glm::ivec2, Node, KeyFuncs, KeyFuncs> path;

	while (true) {
		returnPath.push_back(currentNode);
		if (closedNodes.find(currentNode.getPosition())->second.getPosition() == start) {
			break;
		}
		currentNode = closedNodes.find(currentNode.getPosition())->second;
	}

	return returnPath;
}

Node PathFinder::calculatePath(std::unordered_map<glm::ivec2, Node, KeyFuncs, KeyFuncs>& nodeMap, const glm::vec2 & start, const glm::vec2 & finish)
{
	//priority queue
	std::vector<Node> openNodes;


	std::unordered_map<glm::ivec2, Node, KeyFuncs, KeyFuncs> indivNodeMap;

	Node startNode;
	startNode.init(start, 0);
	startNode.setPreviousPosition(glm::ivec2((int)start.x, (int)start.y));

	indivNodeMap.insert(std::make_pair(startNode.getPosition(), startNode));

	openNodes.push_back(startNode);

	while (openNodes.size() > 0) {

		int i = bestScore(openNodes, finish);
		
		getLocalNodes(openNodes, nodeMap, openNodes[bestScore(openNodes, finish)]);
		
		if (openNodes[i].getPosition() == finish) {

			indivNodeMap.insert(std::make_pair(openNodes[i].getPosition(), openNodes[bestScore(openNodes, finish)]));
			nodeMap.insert(std::make_pair(openNodes[i].getPosition(), indivNodeMap.find(openNodes[i].getPrevPosition())->second));

			return openNodes[i];
		}
		
		indivNodeMap.insert(std::make_pair(openNodes[i].getPosition(), openNodes[i]));
		
		nodeMap.insert(std::make_pair(openNodes[i].getPosition(), indivNodeMap.find(openNodes[i].getPrevPosition())->second));

		openNodes.erase(openNodes.begin() + i);
		
	}

	//failed to find path, user handles error
	std::cout << "No path found" << std::endl;
	return startNode;
}

int PathFinder::bestScore(std::vector<Node>& nodeMap, const glm::vec2& goal)
{	
	//calculates lowest fscore in node list and return index
	float currentBest = nodeMap[0].calculateFScore(goal);
	int bestNode = 0;
	for (int i = 0; i < nodeMap.size(); i++) {
		if (nodeMap[i].calculateFScore(goal) < currentBest) {
			currentBest = nodeMap[i].calculateFScore(goal);
			bestNode = i;
		}
	}

	return bestNode;
}


void PathFinder::getLocalNodes(std::vector<Node> &openNodes, std::unordered_map<glm::ivec2, Node, KeyFuncs, KeyFuncs>& nodeMap, const Node &start)
{
	//calculates nodes in vicinity of current node
	Node constructor;
	glm::vec2 pos;

	glm::vec2 startPos = start.getPosition();

	int weight = start.getWeight() + 1;

	//left
	pos.x = startPos.x - 1.0f;
	pos.y = startPos.y;
	constructor.init(pos, weight);
	constructor.setPreviousPosition(startPos);
	if (isPositionValid(nodeMap, constructor))
		openNodes.push_back(constructor);

	//below
	pos.x = startPos.x;
	pos.y = startPos.y + 1.0f;
	constructor.init(pos, weight);
	constructor.setPreviousPosition(startPos);
	if (isPositionValid(nodeMap, constructor))
		openNodes.push_back(constructor);

	//right
	pos.x = startPos.x + 1.0f;
	pos.y = startPos.y;
	constructor.init(pos, weight);
	constructor.setPreviousPosition(startPos);
	if (isPositionValid(nodeMap, constructor))
		openNodes.push_back(constructor);

	//above
	pos.x = startPos.x;
	pos.y = startPos.y - 1.0f;
	constructor.init(pos, weight);
	constructor.setPreviousPosition(startPos);
	if (isPositionValid(nodeMap, constructor))
		openNodes.push_back(constructor);

	//bottomleft
	pos.x = startPos.x - 1.0f;
	pos.y = startPos.y + 1.0f;
	constructor.init(pos, weight);
	constructor.setPreviousPosition(startPos);
	if (isPositionValid(nodeMap, constructor))
		openNodes.push_back(constructor);

	//top left
	pos.x = startPos.x - 1.0f;
	pos.y = startPos.y - 1.0f;
	constructor.init(pos, weight);
	constructor.setPreviousPosition(startPos);
	if (isPositionValid(nodeMap, constructor))
		openNodes.push_back(constructor);

	//bottom right
	pos.x = startPos.x + 1.0f;
	pos.y = startPos.y + 1.0f;
	constructor.init(pos, weight);
	constructor.setPreviousPosition(startPos);
	if (isPositionValid(nodeMap, constructor))
		openNodes.push_back(constructor);

	//top right
	pos.x = startPos.x + 1.0f;
	pos.y = startPos.y - 1.0f;
	constructor.init(pos, weight);
	constructor.setPreviousPosition(startPos);
	if (isPositionValid(nodeMap, constructor))
		openNodes.push_back(constructor);
	
}

bool PathFinder::isPositionValid(const std::unordered_map<glm::ivec2, Node, KeyFuncs, KeyFuncs>& nodeMap, const Node & myNode)
{
	glm::vec2 pos = myNode.getPosition();
	return pos.x >= 0.0f && pos.y >= 0.0f && pos.y < m_map.size() && m_map[0].size() > pos.x && m_map[pos.y][pos.x] != 1 && nodeMap.find(pos) == nodeMap.end();
}
