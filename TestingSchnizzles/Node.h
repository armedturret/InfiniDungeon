#pragma once
#include <glm\glm.hpp>

class Node
{
public:
	Node();
	~Node();

	void init(glm::vec2 position, int weight);

	float calculateFScore(const glm::vec2& goal);

	glm::vec2 getPosition() const { return m_position; };

	int getWeight() const { return m_weight; };

	glm::ivec2 getPrevPosition() const { return m_prevPos; };

	void setPreviousPosition(const glm::ivec2& pos) { m_prevPos = pos; }

private:
	glm::ivec2 m_prevPos;

	glm::vec2 m_position;

	int m_weight;
	
};

