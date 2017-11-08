#pragma once
class Random
{
public:
	Random();
	~Random();

	static int randInt(int min, int max);

	static float randFloat(float min, float max);
};

