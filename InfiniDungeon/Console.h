#pragma once
#include <thread>
#include <functional>

class Console
{
public:
	Console();
	~Console();

	//the  console will function as such
	//it will hold a refrence to all the current things it needs to manage
	//it will also operate in a seperate thread

	void init();

	void destroy();

private:
	bool m_shouldEndThread = false;

	//console thread
	std::thread console;

};

//seperate class for runtime
class ConsoleRun
{
friend Console;

private:
	static std::string getLineFromCin();
	//console function
	static int run(std::thread& consoleThread, bool& shouldEndThread);
};