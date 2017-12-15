#include "Console.h"
#include <iostream>
#include <chrono>
#include <future>
#include <string>
Console::Console()
{
}


Console::~Console()
{
}

void Console::init()
{
	m_shouldEndThread = false;
	console = std::thread(ConsoleRun::run, std::ref(console), std::ref(m_shouldEndThread));
	std::cout << "Console thread initialized; Id: " << console.get_id() << std::endl;;
}

void Console::destroy()
{
	
	m_shouldEndThread = true;
	while (console.joinable()) {

	}
	std::cout << "Console thread joined" << std::endl;
}

std::string ConsoleRun::getLineFromCin()
{
	std::string line;
	std::getline(std::cin, line);
	return line;
}

int ConsoleRun::run(std::thread& consoleThread, bool& shouldEndThread)
{
	auto future = std::async(std::launch::async, getLineFromCin);

	while (!shouldEndThread) {
		if (future.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
			auto line = future.get();

			future = std::async(std::launch::async, getLineFromCin);

			//do command processing here
		}
	}
	consoleThread.detach();
	return 0;
}
