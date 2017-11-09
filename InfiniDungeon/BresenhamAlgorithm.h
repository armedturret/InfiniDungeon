#pragma once
#include <glm/glm.hpp>
#include <vector>

class BresenhamAlgorithm
{
public:
	BresenhamAlgorithm();
	~BresenhamAlgorithm();

	bool canSeePoint(const std::vector<std::vector<int>>& map, glm::ivec2 startPos, glm::ivec2 endPos);
private:
	bool isTileSolid(const std::vector<std::vector<int>>& map, const glm::ivec2& checkPos);
};
