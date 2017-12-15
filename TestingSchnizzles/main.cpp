/*#include "PathFinderTest.h"

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
}*/
#include <iostream>
#include <chrono>
#include <future>
#include <string>

std::string GetLineFromCin() {
	std::string line;
	std::getline(std::cin, line);
	return line;
}

int main() {

	auto future = std::async(std::launch::async, GetLineFromCin);

	while (true) {
		if (future.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
			auto line = future.get();

			// Set a new line. Subtle race condition between the previous line
			// and this. Some lines could be missed. To aleviate, you need an
			// io-only thread. I'll give an example of that as well.
			future = std::async(std::launch::async, GetLineFromCin);

			std::cout << "you wrote " << line << std::endl;
		}

		std::cout << "waiting..." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}