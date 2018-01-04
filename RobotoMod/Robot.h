#pragma once
#include <Enemy.h>

class Robot:public Enemy
{
public:
	Robot();
	~Robot();
	
	virtual void sayHy()override;
};

__declspec(dllexport) Enemy* create_enemy() { return new Robot(); }
__declspec(dllexport) void delete_enemy(Enemy* enemy) { delete enemy; }
