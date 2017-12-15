#include "Console.h"
#include <iostream>
#include <string>
Console::Console()
{
}


Console::~Console()
{
}

void Console::init()
{
	console = std::thread(ConsoleRun::run, std::ref(console));
	std::cout << "Console thread initialized; Id: " << console.get_id() << std::endl;;
}

void Console::destroy()
{
	std::cout << "Console thread joined" << std::endl;
}

int ConsoleRun::run(std::thread& consoleThread)
{
	std::string a;
	std::getline(std::cin, a);
	std::cout << a << std::endl;

	consoleThread.detach();
	return 0;
}
