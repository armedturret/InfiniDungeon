#include "PathFinderTest.h"

#include <string>
#include <iostream>
#include <ctime>

#include "VisionStuff.h"

int main() {
	std::clock_t  startTime;

	startTime = std::clock();

	VisionStuff test;
	test.Run();

	std::cout << "Test finished in " << (std::clock() - startTime) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

	std::string a;
	std::getline(std::cin, a);
	return 0;
}