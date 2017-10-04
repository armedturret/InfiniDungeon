#pragma once
#include <glm\glm.hpp>

class Node
{
public:
	Node(glm::vec2 location, int weight);
	~Node();

	glm::vec2 getPosition() const { return m_position; };

private:
	glm::vec2 m_position;
	int m_weight;
};

