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

int main() {
	std::vector<std::string> b;
	listFile(b);
	std::string a;
	for (auto s : b) {
		std::ifstream reader;
		reader.open("./mods/" + s);
		reader >> a;
		std::cout << a << "\n";
	}
	std::vector<Enemy*> enemies;
	enemies.push_back(new ScaryBoi());

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