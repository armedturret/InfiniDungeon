#pragma once

#include <DPE\SpriteBatch.h>
#include <DPE\DebugRender.h>
#include <DPE\GLSLProgram.h>
#include <vector>

#include "Themes.h"

const int TILE_SIZE = 128;

const int ROWS = 40;
const int COLUMNS = 40;

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

	void draw();

	void dispose();

	void setEntMap(const std::vector<std::vector<int>>& entMap) { m_entMap = entMap; }

	glm::ivec2 getStartPos() const { return m_startPos; }

	std::vector<std::vector<int>> getMap() const { return m_map; };
	std::vector<std::vector<int>> getEntMap() const { return m_entMap; };

private:

	void drawEntTiles();

	void generatePerfMaze();

	//TODO: Add some enum for room algorithm
	void generateRooms(int rows, int columns);

	void getAdjacentTiles(const glm::ivec2& startNode, std::vector<glm::ivec2>& output);

	bool isTileValid(glm::ivec2 checkTile);

	void makeConnectors();

	void removeDeadEnds();

	bool isTileLonely(const glm::ivec2& pos, glm::ivec2 & possibleConnector);

	bool amILonely();

	bool checkRoomCollisions(const Room& room, int rows, int columns);

	bool doesRoomCollide(const Room& room1, const Room& room2);

	bool isPosRoom(const glm::ivec2& pos, const Room& room);

	bool hasAdjacentTile(const glm::ivec2& pos, const Room& room);

	int randInt(int min, int max);

	float randFloat(float min, float max);

	DPE::SpriteBatch m_spriteBatch;
	//Only m_entBatch is updateable
	DPE::SpriteBatch m_entBatch;

	std::vector<Room> m_rooms;
	std::vector<std::vector<int>> m_map;
	//Stores info about different entities i.e. Is a door open
	std::vector<std::vector<int>> m_entMap;
	std::vector<glm::ivec2> m_corridors;

	glm::ivec2 m_startPos;

	theme m_theme;
};

