#include "Level.h"

#include <DPE/ResourceManager.h>

#include <iostream>
#include <fstream>
#include <random>
#include <ctime>

Level::Level():m_startPos(2)
{
}


Level::~Level()
{
}



void Level::init(int difficulty)
{

	//choose a theme of matching difficulty
	if (difficulty == 1) {
		//TODO: Remove json code due to being dumb

		static std::mt19937 randomEngine(time(nullptr));
		std::uniform_int_distribution<int> randInt(0, sizeof(levelOne) / sizeof(levelOne[0]) - 1);
		//choose random theme
		int index = randInt(randomEngine);

		m_theme = levelOne[index];
	}
	else {
		std::cout << "difficulty not valid" << std::endl;
	}

	int rows = 30;
	int columns = 30;

	//reserve the map 
	m_map.resize(rows);

	for (int r = 0; r < rows; r++)
		m_map[r].resize(columns, 1);

	//!!IMPORTANT all spacing must be in multiples of 2 because spacing

	//rooms first
	generateRooms(rows, columns);

	//Populate with corridors
	generatePerfMaze();
	
	//connect corridors to rooms
	makeConnectors();

	//remove dead ends
	removeDeadEnds();

	m_spriteBatch.init();

	m_debugRenderer.init();

	m_spriteBatch.begin();
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < columns; x++) {
			glm::vec4 destRect;
			destRect.x = x*TILE_SIZE;
			destRect.y = y*TILE_SIZE;
			destRect.z = TILE_SIZE;
			destRect.w = TILE_SIZE;
			float angle = 0.0f;
			std::string texture;
			GLubyte r = 255;
			GLubyte b = 255;
			if (m_map[y][x] == 0) {
				texture = "Data/Textures/Themes/" + m_theme.name + "/" + m_theme.floor;
			}
			else if (m_map[y][x] == 1) {
				texture = "Data/Textures/Themes/" + m_theme.name + "/"+ m_theme.wall;
			}
			else if (m_map[y][x] == 2) {
				r = 0;
				texture = "Data/Textures/Themes/" + m_theme.name + "/" + m_theme.wall;
			}
			else if (m_map[y][x] == 3) {
				b = 127;
				texture = "Data/Textures/Themes/" + m_theme.name + "/" + m_theme.wall;
			}
			m_spriteBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), DPE::ResourceManager::getTexture(texture).id, 0.0f, DPE::ColorRGBA8(r, 255, 255, b), angle);
		}
	}
	m_spriteBatch.end();
}

void Level::draw(glm::mat4& projectionMatrix, DPE::GLSLProgram & program)
{
	m_spriteBatch.renderBatch();
	m_debugRenderer.render(projectionMatrix, 2.0f);
	program.use();
}

void Level::dispose()
{
	m_spriteBatch.dispose();
	m_debugRenderer.dispose();
}

void Level::generatePerfMaze()
{
	std::cout << "Generating perfect maze" << std::endl;
	glm::ivec2 currentNode = glm::ivec2(2);
	std::vector<glm::ivec2> openList;

	openList.push_back(currentNode);
	m_corridors.push_back(currentNode);

	while (openList.size() > 0) {
		m_map[currentNode.y][currentNode.x] = 0;
		std::vector<glm::ivec2> localTiles;
		getAdjacentTiles(openList[openList.size() - 1], localTiles);

		if (localTiles.size() == 0) {
			openList.erase(openList.begin() + openList.size() - 1);
		}
		else {
			int dir = (randInt(0, (localTiles.size() / 2) - 1) * 2);
			//set current tile
			currentNode.x = localTiles[dir].x;
			currentNode.y = localTiles[dir].y;
			m_corridors.push_back(currentNode);

			//create inbetween tile
			m_map[localTiles[dir + 1].y][localTiles[dir + 1].x] = 0;
			openList.push_back(currentNode);

		}
		localTiles.clear();

	}
	std::cout << "Finished perfect maze!" << std::endl;
}

void Level::generateRooms(int rows, int columns)
{
	//min and max in space for length always will be even
	int minLength = 1;
	int maxLength = 4;

	//atempts to make a room
	//will be the max area divide by the maxArea and should be have of total space
	int attempts = rows * columns / (minLength*minLength);
	std::cout << "Populating with rooms at " << attempts << " attempts before termination." << std::endl;

	for (int i = 0; i < attempts; i++) {
		Room room;

		glm::vec4 destRect;

		//length
		destRect.z = randInt(minLength, maxLength) * 2 + 1;
		//height
		destRect.w = randInt(minLength, maxLength) * 2 + 1;

		destRect.x = randInt(2, (columns - 2) / 2) * 2;
		destRect.y = randInt(2, (rows - 2) / 2) * 2;

		room.destRect = destRect;

		if (checkRoomCollisions(room, rows, columns)) {
			
			//set start pos
			if (m_rooms.size() == 0) {
				std::cout << "Setting player pos "<< room.destRect.x << std::endl;
				//first room is start
				m_startPos.x = room.destRect.x + (room.destRect.z - 1) / 2;
				m_startPos.y = room.destRect.y + (room.destRect.w - 1) / 2;
				std::cout << m_startPos.x << " " << m_startPos.y << std::endl;
			}

			//add rooms to map
			m_rooms.push_back(room);


			//Add it to the maze
			for (int r = 0; r < room.destRect.w; r++) {
				for (int c = 0; c < room.destRect.z; c++) {
					//height and than width
					m_map[r + room.destRect.y][c + room.destRect.x] = 0;
				}
			}
		}
	}
	
	std::cout << "Finished rooms!" << std::endl;
}

void Level::getAdjacentTiles(const glm::ivec2 & startNode, std::vector<glm::ivec2>& output)
{
	//up
	glm::vec2 temp;
	glm::vec2 midTemp;
	temp.x = startNode.x;
	temp.y = startNode.y - 2;
	//tile to reach the next one
	midTemp.x = startNode.x;
	midTemp.y = startNode.y - 1;
	if (isTileValid(temp)) {
		output.push_back(temp);
		output.push_back(midTemp);
	}

	//down
	temp.x = startNode.x;
	temp.y = startNode.y + 2;
	//tile to reach the next one
	midTemp.x = startNode.x;
	midTemp.y = startNode.y + 1;
	if (isTileValid(temp)) {
		output.push_back(temp);
		output.push_back(midTemp);
	}

	//left
	temp.x = startNode.x - 2;
	temp.y = startNode.y;
	//tile to reach the next one
	midTemp.x = startNode.x - 1;
	midTemp.y = startNode.y;
	if (isTileValid(temp)) {
		output.push_back(temp);
		output.push_back(midTemp);
	}

	//right
	temp.x = startNode.x + 2;
	temp.y = startNode.y;
	//tile to reach the next one
	midTemp.x = startNode.x + 1;
	midTemp.y = startNode.y;
	if (isTileValid(temp)) {
		output.push_back(temp);
		output.push_back(midTemp);
	}
}

bool Level::isTileValid(glm::ivec2 checkTile)
{
	//check if out of map
	if (m_map.size() >= checkTile.x + 1 &&
		0 < checkTile.x - 1 &&
		m_map[0].size() >= checkTile.y + 1 &&
		0 < checkTile.y - 1)

		//right, left, up, down, upleft...
		if (m_map[checkTile.y + 1][checkTile.x] == 1 &&
			m_map[checkTile.y - 1][checkTile.x] == 1 &&
			m_map[checkTile.y][checkTile.x - 1] == 1 &&
			m_map[checkTile.y][checkTile.x + 1] == 1 &&
			m_map[checkTile.y+1][checkTile.x + 1] == 1 && 
			m_map[checkTile.y-1][checkTile.x + 1] == 1 && 
			m_map[checkTile.y+1][checkTile.x - 1] == 1 && 
			m_map[checkTile.y-1][checkTile.x - 1] == 1)
			return true;

	return false;
}

void Level::makeConnectors()
{
	std::cout << "Connecting passages..." << std::endl;
	std::vector<glm::ivec2> possibleConnections;
	glm::ivec2 tmp = glm::ivec2(0);
	for (auto r : m_rooms) {

		//perform bottom edge
		for (int i = 0; i < r.destRect.z; i++) {
			tmp.x = r.destRect.x + i;
			tmp.y = r.destRect.y - 1;

			if (hasAdjacentTile(tmp, r)) {
				possibleConnections.push_back(tmp);
			}
		}

		//top edge
		for (int i = 0; i < r.destRect.z; i++) {
			tmp.x = r.destRect.x + i;
			tmp.y = r.destRect.y + r.destRect.w;
			
			if (hasAdjacentTile(tmp, r)) {
				possibleConnections.push_back(tmp);
			}
		}

		//left edge
		for (int i = 0; i < r.destRect.w; i++) {
			tmp.x = r.destRect.x - 1;
			tmp.y = r.destRect.y + i;
			
			if (hasAdjacentTile(tmp, r)) {
				possibleConnections.push_back(tmp);
			}
		}

		//right edge
		for (int i = 0; i < r.destRect.w; i++) {
			tmp.x = r.destRect.x + r.destRect.z;
			tmp.y = r.destRect.y + i;
			
			if (hasAdjacentTile(tmp, r)) {
				possibleConnections.push_back(tmp);
			}
		}
		
		if (possibleConnections.size()>0) {
			//open a random one
			int connector = randInt(0, possibleConnections.size() - 1);
			m_map[possibleConnections[connector].y][possibleConnections[connector].x] = 0;

			if (connector > 0) {
				possibleConnections.erase(possibleConnections.begin() + connector - 1);
				connector -= 1;
			}

			if (connector < possibleConnections.size() - 1) {
				possibleConnections.erase(possibleConnections.begin() + connector + 1);
			}

			possibleConnections.erase(possibleConnections.begin() + connector);

			for (auto g : possibleConnections) {
				//possibly open second tile
				int posib = randInt(1, 30);
				if(posib == 1)
					m_map[g.y][g.x] = 0;
			}

			//prepare for new loop
			possibleConnections.clear();
			
		}
		else {

		}
	}

	std::cout << "Finished" << std::endl;
}

void Level::removeDeadEnds()
{
	std::cout << "Removing dead ends" << std::endl;

	//remove dead ends
	for (int i = 0; i < m_corridors.size(); i++) {
		//holds single tile touching tile
		glm::ivec2 touchyTileThing(0);
		//throwaway var
		glm::ivec2 filler(0);
		glm::ivec2 fillerThingy(0);
		glm::ivec2 fillerfiller(0);

		if (isTileLonely(m_corridors[i], touchyTileThing)) {
			m_map[m_corridors[i].y][m_corridors[i].x] = 1;
			if (isTileLonely(touchyTileThing, filler))
				m_map[touchyTileThing.y][touchyTileThing.x] = 1;

			m_corridors.erase(m_corridors.begin() + i);

			i = -1;
		}
	}

	std::cout << "Finished" << std::endl;
}

bool Level::isTileLonely(const glm::ivec2 & pos, glm::ivec2 & possibleConnector)
{
	//checks if the tile is connected to other tiles
	int localTiles = 0;
	//up
	glm::vec2 temp;
	temp.x = pos.x;
	temp.y = pos.y - 1;
	if (m_map[temp.y][temp.x] == 0) {
		localTiles += 1;
		possibleConnector = temp;
	}

	//down
	temp.x = pos.x;
	temp.y = pos.y + 1;
	if (m_map[temp.y][temp.x] == 0) {
		localTiles += 1;
		possibleConnector = temp;
	}

	//left
	temp.x = pos.x - 1;
	temp.y = pos.y;
	if (m_map[temp.y][temp.x] == 0) {
		localTiles += 1;
		possibleConnector = temp;
	}

	//right
	temp.x = pos.x + 1;
	temp.y = pos.y;
	if (m_map[temp.y][temp.x] == 0) {
		localTiles += 1;
		possibleConnector = temp;
	}

	if (localTiles < 2 ) {
		return true;
	}
	else {
		return false;
	}
}

bool Level::amILonely()
{
	//calculate if I'm lonely
	int friends = 0;

	if (friends > 0) {
		return false;
	}
	else {
		return true;
	}
}

bool Level::checkRoomCollisions(const Room & room, int rows, int columns)
{
	//check if out of map
	if (room.destRect.x + room.destRect.z > columns - 1 ||
		room.destRect.y + room.destRect.w > rows - 1)
		return false;

	for (int b = 0; b < m_rooms.size(); b++/*the equivelant of an A- XD*/) {
		if (doesRoomCollide(room, m_rooms[b])) {
			return false;
		}
	}

	return true;
}

bool Level::doesRoomCollide(const Room & room1, const Room & room2)
{
	glm::vec4 rect1 = room1.destRect;
	glm::vec4 rect2 = room2.destRect;

	//AABB collision
	if (rect1.x - 1 < rect2.x + rect2.z + 1 &&
		rect1.x + rect1.z + 1 > rect2.x - 1 &&
		rect1.y - 1< rect2.y + rect2.w + 1 &&
		rect1.w + rect1.y + 1 > rect2.y - 1) {
		return true;
	}
	return false;
}

bool Level::isPosRoom(const glm::ivec2 & pos, const Room & room)
{
	glm::vec4 rect2 = room.destRect;
	glm::vec2 rect1 = pos;

	//AABB collision
	if (rect1.x <= rect2.x + rect2.z &&
		rect1.x >= rect2.x &&
		rect1.y <= rect2.y + rect2.w  &&
		rect1.y >= rect2.y) {
		return true;
	}
	return false;
}

bool Level::hasAdjacentTile(const glm::ivec2 & pos, const Room & room)
{
	//checks if the tile connects to maze and is not a room
	//up
	glm::vec2 temp;
	temp.x = pos.x;
	temp.y = pos.y - 1;
	if (!isPosRoom(temp,room) && temp.y > 0 && temp.x > 0 && temp.y < m_map.size() && temp.x < m_map[0].size() && m_map[temp.y][temp.x] == 0) {
		return true;
	}

	//down
	temp.x = pos.x;
	temp.y = pos.y + 1;
	if (!isPosRoom(temp, room) && temp.y > 0 && temp.x > 0 && temp.y < m_map.size() && temp.x < m_map[0].size() && m_map[temp.y][temp.x] == 0) {
		return true;
	}

	//left
	temp.x = pos.x - 1;
	temp.y = pos.y;
	if (!isPosRoom(temp, room) && temp.y > 0 && temp.x > 0 && temp.y < m_map.size() && temp.x < m_map[0].size() && m_map[temp.y][temp.x] == 0) {
		return true;
	}

	//right
	temp.x = pos.x + 1;
	temp.y = pos.y;
	if (!isPosRoom(temp, room) && temp.y > 0 && temp.x > 0 && temp.y < m_map.size() && temp.x < m_map[0].size() && m_map[temp.y][temp.x] == 0) {
		return true;
	}

	return false;
}

int Level::randInt(int min, int max)
{
	//improved version of rand() from <random>
	static std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int> randInteger(min, max);

	return randInteger(randomEngine);
}

float Level::randFloat(float min, float max)
{
	//improved version of rand() from <random>
	static std::mt19937 randomEngine(time(nullptr));
	std::uniform_real_distribution<float> randomFloat(min, max);

	return randomFloat(randomEngine);
}