#pragma once

#include <DPE\SpriteBatch.h>
#include <DPE\DebugRender.h>
#include <DPE\GLSLProgram.h>
#include <vector>

#include "Themes.h"

const int TILE_SIZE = 128;

struct Room {
	glm::ivec4 destRect;
};

struct NotKeyFuncs
{
	size_t operator()(const glm::ivec2& k)const
	{
		return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
	}

	bool operator()(const glm::ivec2& a, const glm::ivec2& b)const
	{
		return a.x == b.x && a.y == b.y;
	}
};

class Level
{
public:
	Level();
	~Level();

	void init(int difficulty);

	void draw(glm::mat4& projectionMatrix, DPE::GLSLProgram & program);

	void dispose();

	std::vector<std::vector<int>> getMap() const { return m_map; };

private:

	void generatePerfMaze();

	//TODO: Add some enum for room algorithm
	void generateRooms(int rows, int columns);

	void getAdjacentTiles(const glm::ivec2& startNode, std::vector<glm::ivec2>& output);

	bool isTileValid(glm::ivec2 checkTile);

	void makeConnectors();

	void removeDeadEnds();

	bool checkRoomCollisions(const Room& room, int rows, int columns);

	bool doesRoomCollide(const Room& room1, const Room& room2);

	bool isPosRoom(const glm::ivec2& pos, const Room& room);

	bool hasAdjacentTile(const glm::ivec2& pos, const Room& room);

	int randInt(int min, int max);

	float randFloat(float min, float max);

	DPE::SpriteBatch m_spriteBatch;
	DPE::DebugRender m_debugRenderer;

	std::vector<Room> m_rooms;
	std::vector<std::vector<int>> m_map;
	std::vector<glm::ivec2> m_corridors;

	theme m_theme;
};

