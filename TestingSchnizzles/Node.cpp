#include "Node.h"



Node::Node()
{
}


Node::~Node()
{
}

void Node::init(glm::vec2 position, int weight)
{
	m_position.x = position.x;
	m_position.y = position.y;

	m_weight = weight;
}

float Node::calculateFScore(const glm::vec2& goal)
{
	//first, calculate the hueristic
	//we will use diagonal distance
	//use diagonal distance for main game
	float h = sqrt(pow(goal.x - m_position.x, 2.0f) + pow(goal.y - m_position.y, 2.0f));
	h *= 2.0f;
	h = floor(h);
	
	//slight nudge to break ties
	float p = 1.0f / 1000.0f;
	h *= (1.0 + p);

	return h + m_weight;
}
