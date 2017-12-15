#include "Console.h"
#include <iostream>
#include <chrono>
#include <future>
#include <string>
#include <sstream>
#include <iterator>
Console::Console()
{
}


Console::~Console()
{
}

void Console::init()
{
	Command::create_map();

	//make commands
	Command::create(Console::help, CommandInfo("help", "Stop it. Get some help.", "help OR help <pagenum> OR help <command>"));
	Command::create(Console::echo, CommandInfo("echo", "Prints text that follows.", "echo <words..>"));

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

int Console::help(std::vector<std::string> args)
{
	std::cout << "My name is jeff" << std::endl;
	return 0;
}

int Console::echo(std::vector<std::string> args)
{
	if (args.size() > 1) {
		std::cout << "[echo]: ";
		for (int i = 1; i < args.size(); i++)
			std::cout << args[i] << " ";
		std::cout << "\n";
		return 0;
	}
	else {
		return 1;
	}
	
}

std::string ConsoleRun::getLineFromCin()
{
	std::string line;
	std::getline(std::cin, line);
	return line;
}

int ConsoleRun::processCommand(std::string input)
{
	std::istringstream iss(input);
	std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss},
		std::istream_iterator<std::string>{} };
	if (tokens.size() > 0) {
		Command cmd = Command::get_map().find(tokens[0])->second;
		if (cmd.m_handler(tokens) == 1) {
			std::cout << cmd.cmdInfo.helphint << std::endl;
		}
	}
	return 0;
}

int ConsoleRun::run(std::thread& consoleThread, bool& shouldEndThread)
{
	auto future = std::async(std::launch::async, getLineFromCin);
	
	while (!shouldEndThread) {
		if (future.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
			auto line = future.get();

			future = std::async(std::launch::async, getLineFromCin);

			processCommand(line);
		}
	}
	consoleThread.detach();
	return 0;
}

void Command::create(int(&handler)(std::vector<std::string>args), const CommandInfo & infoObject)
{
	Command tmpCommand;
	tmpCommand.m_handler = &handler;
	tmpCommand.cmdInfo = infoObject;
	Command::get_map().insert(std::make_pair(tmpCommand.cmdInfo.name,tmpCommand));
}
