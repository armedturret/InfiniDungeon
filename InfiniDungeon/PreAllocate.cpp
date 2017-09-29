#include "PreAllocate.h"
#include<iostream>
#include <DPE/ResourceManager.h>
#include <vector>

void PreAllocate::loadTextures() {
	std::vector<std::string> textures = { "Floor.png","Wall.png","Mage.png" };

	//preallocate textures for faster run speed
	for (int i = 0; i < textures.size(); i++) {
		std::cout << "Precaching textures "<< "Data/Textures/" + textures[i] <<"[" << i + 1 << "/" << textures.size() << "]" << std::endl;
		DPE::ResourceManager::getTexture("Data/Textures/"+textures[i]);
	}
}