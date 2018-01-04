#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<string>
#include<fstream>
#include<dirent\dirent.h>
#include<vector>
#include <Enemy.h>

#include "ScaryBoi.h"

void listFile(std::vector<std::string>& files);

typedef Enemy* (*create_enemy)();

int main() {
	std::vector<HINSTANCE> libs;
	std::vector<std::string> b;
	std::vector<Enemy*> enemies;
	listFile(b);
	std::string a;
	for (auto s : b) {
		//load dlls
		a = "./mods/" + s;
		HINSTANCE temp = LoadLibrary(a.c_str());
		libs.push_back(temp);
		if (!temp) {
			std::cout << "could not load the dynamic library" << std::endl;
			std::getline(std::cin, a);
			return EXIT_FAILURE;
		}
		// resolve function address here
		create_enemy enemyFunc = (create_enemy)GetProcAddress(temp, "create_enemy");
		if (!enemyFunc) {
			std::cout << "could not locate the function" << std::endl;
			std::getline(std::cin, a);
			return EXIT_FAILURE;
		}
		else {
			enemies.push_back(enemyFunc());
		}
	}
	
	enemies.push_back(new ScaryBoi());
	
	for (auto e : enemies) {
		std::cout << e->getName() << std::endl;
	}

	while (true) {
		std::getline(std::cin, a);
		for (auto e : enemies) {
			if (e->getName() == a) {
				e->sayHy();
			}
		}
		if (a == "exit") {
			break;
		}
	}

	for (int i = 0; i < enemies.size(); i++) {
		delete enemies[i];
		enemies.erase(enemies.begin() + i);
		i--;
	}

	for (int i = 0; i < libs.size(); i++) {
		FreeLibrary(libs[i]);
		libs.erase(libs.begin() + i);
		i--;
	}

	return 0;
}

void listFile(std::vector<std::string>& files) {
	DIR *pDIR;
	struct dirent *entry;
	if (pDIR = opendir("./mods")) {
		while (entry = readdir(pDIR)) {
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
				files.push_back(entry->d_name);
		}
		closedir(pDIR);
	}
}