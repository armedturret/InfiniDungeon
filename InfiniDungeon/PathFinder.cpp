#include "PathFinder.h"
#include <iostream>
#include <algorithm>
PathFinder::PathFinder()
{
}


PathFinder::~PathFinder()
{
}

std::vector<Node> PathFinder::pathBetweenPoints(const glm::vec2& end, const glm::vec2& start, const std::vector<std::vector<int>>& map)
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

	//add extra node
	Node goalNode;
	goalNode.init(start, returnPath.size());

	returnPath.push_back(goalNode);
	return returnPath;
}

Node PathFinder::calculatePath(std::unordered_map<glm::ivec2, Node, KeyFuncs, KeyFuncs>& nodeMap, const glm::vec2 & start, const glm::vec2 & finish)
{
	//priority queue
	std::vector<Node> openNodes;

	//for faster fscore calculations
	//<index, FScore>
	std::map<int, float> indexTracker;

	std::unordered_map<glm::ivec2, Node, KeyFuncs, KeyFuncs> indivNodeMap;

	Node startNode;
	startNode.init(start, 0);
	startNode.setPreviousPosition(glm::ivec2((int)start.x, (int)start.y));

	indivNodeMap.insert(std::make_pair(startNode.getPosition(), startNode));

	openNodes.push_back(startNode);
	indexTracker.insert(std::make_pair(openNodes.size() - 1, startNode.calculateFScore(finish)));

	while (openNodes.size() > 0) {

		int i = bestScore(openNodes, finish, indexTracker);
		
		//purge if already checked to prevent clones
		if (isPositionValid(nodeMap, openNodes[i])) {

			getLocalNodes(openNodes, nodeMap, openNodes[i], finish, indexTracker);

			if (openNodes[i].getPosition() == finish) {

				indivNodeMap.insert(std::make_pair(openNodes[i].getPosition(), openNodes[bestScore(openNodes, finish, indexTracker)]));
				nodeMap.insert(std::make_pair(openNodes[i].getPosition(), indivNodeMap.find(openNodes[i].getPrevPosition())->second));

				return openNodes[i];
			}

			indivNodeMap.insert(std::make_pair(openNodes[i].getPosition(), openNodes[i]));

			nodeMap.insert(std::make_pair(openNodes[i].getPosition(), indivNodeMap.find(openNodes[i].getPrevPosition())->second));
		}

		indexTracker.erase(i);
		
	}

	//failed to find path, user handles error
	std::cout << "No path found" << std::endl;
	return startNode;
}

int PathFinder::bestScore(std::vector<Node>& nodeMap, const glm::vec2& goal, const std::map<int, float>& indexTracker)
{	
	auto min
		= *min_element(indexTracker.begin(), indexTracker.end(), CompareSecond());

	return min.first;
}


void PathFinder::getLocalNodes(std::vector<Node> &openNodes, std::unordered_map<glm::ivec2, Node, KeyFuncs, KeyFuncs>& nodeMap, const Node &start, const glm::vec2 &goal, std::map<int, float>& indexTracker)
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
	if (isPositionValid(nodeMap, constructor)) {
		openNodes.push_back(constructor);
		indexTracker.insert(std::make_pair(openNodes.size() - 1, constructor.calculateFScore(goal)));
	}

	//below
	pos.x = startPos.x;
	pos.y = startPos.y + 1.0f;
	constructor.init(pos, weight);
	constructor.setPreviousPosition(startPos);
	if (isPositionValid(nodeMap, constructor)) {
		openNodes.push_back(constructor);
		indexTracker.insert(std::make_pair(openNodes.size() - 1, constructor.calculateFScore(goal)));
	}

	//right
	pos.x = startPos.x + 1.0f;
	pos.y = startPos.y;
	constructor.init(pos, weight);
	constructor.setPreviousPosition(startPos);
	if (isPositionValid(nodeMap, constructor)) {
		openNodes.push_back(constructor);
		indexTracker.insert(std::make_pair(openNodes.size() - 1, constructor.calculateFScore(goal)));
	}

	//above
	pos.x = startPos.x;
	pos.y = startPos.y - 1.0f;
	constructor.init(pos, weight);
	constructor.setPreviousPosition(startPos);
	if (isPositionValid(nodeMap, constructor)) {
		openNodes.push_back(constructor);
		indexTracker.insert(std::make_pair(openNodes.size() - 1, constructor.calculateFScore(goal)));
	}

	//bottomleft
	pos.x = startPos.x - 1.0f;
	pos.y = startPos.y + 1.0f;
	constructor.init(pos, weight);
	constructor.setPreviousPosition(startPos);
	if (isPositionValid(nodeMap, constructor)) {
		openNodes.push_back(constructor);
		indexTracker.insert(std::make_pair(openNodes.size() - 1, constructor.calculateFScore(goal)));
	}

	//top left
	pos.x = startPos.x - 1.0f;
	pos.y = startPos.y - 1.0f;
	constructor.init(pos, weight);
	constructor.setPreviousPosition(startPos);
	if (isPositionValid(nodeMap, constructor)) {
		openNodes.push_back(constructor);
		indexTracker.insert(std::make_pair(openNodes.size() - 1, constructor.calculateFScore(goal)));
	}

	//bottom right
	pos.x = startPos.x + 1.0f;
	pos.y = startPos.y + 1.0f;
	constructor.init(pos, weight);
	constructor.setPreviousPosition(startPos);
	if (isPositionValid(nodeMap, constructor)) {
		openNodes.push_back(constructor);
		indexTracker.insert(std::make_pair(openNodes.size() - 1, constructor.calculateFScore(goal)));
	}

	//top right
	pos.x = startPos.x + 1.0f;
	pos.y = startPos.y - 1.0f;
	constructor.init(pos, weight);
	constructor.setPreviousPosition(startPos);
	if (isPositionValid(nodeMap, constructor)) {
		openNodes.push_back(constructor);
		indexTracker.insert(std::make_pair(openNodes.size() - 1, constructor.calculateFScore(goal)));
	}
}

bool PathFinder::isPositionValid(const std::unordered_map<glm::ivec2, Node, KeyFuncs, KeyFuncs>& nodeMap, const Node & myNode)
{
	glm::vec2 pos = myNode.getPosition();
	return pos.x >= 0.0f && pos.y >= 0.0f && pos.y < m_map.size() && m_map[0].size() > pos.x && m_map[pos.y][pos.x] != 1 && nodeMap.find(pos) == nodeMap.end();
}
