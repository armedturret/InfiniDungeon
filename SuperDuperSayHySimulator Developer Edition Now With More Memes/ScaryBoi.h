#pragma once
#include <Enemy.h>
#include <iostream>
class ScaryBoi : public Enemy
{
public:
	ScaryBoi();
	~ScaryBoi();
	
	virtual void sayHy() {
		std::cout << "Hello there" << std::endl;
	};
};

