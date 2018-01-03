#pragma once
#include <string>
#include <iostream>
class Enemy
{
public:
	Enemy();
	~Enemy();
	//test mod library
	virtual void sayHy() {
		std::cout << "Hy" << std::endl;
	};

	std::string getName() const { return name; }

protected:
	std::string name;
};

