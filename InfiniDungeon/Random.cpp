#include "Random.h"

#include <random>
#include <ctime>


Random::Random()
{
}


Random::~Random()
{
}

int Random::randInt(int min, int max)
{
	//improved version of rand() from <random>
	static std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int> randInteger(min, max);

	return randInteger(randomEngine);
}

float Random::randFloat(float min, float max)
{
	//improved version of rand() from <random>
	static std::mt19937 randomEngine(time(nullptr));
	std::uniform_real_distribution<float> randomFloat(min, max);

	return randomFloat(randomEngine);
}