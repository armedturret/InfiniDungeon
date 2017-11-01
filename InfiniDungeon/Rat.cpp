#include "Rat.h"

#include <DPE/ResourceManager.h>

Rat::Rat()
{
}


Rat::~Rat()
{
}

void Rat::OnCreation(const std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& entMap)
{
	m_health = 10;

	m_lore = "A nasty sewer creature that somehow grew to the size of a man.";
	m_name = "Giant Rat";

	m_tileSheet.init(DPE::ResourceManager::getTexture("Data/Textures/Themes/Basic/Enemies/" + m_name+".png"), glm::ivec2(4, 2));

	m_animTile = 1;
}
