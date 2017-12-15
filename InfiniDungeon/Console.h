#pragma once
#include <thread>
#include <functional>
#include <vector>
#include <unordered_map>

class Console
{
	
	friend class ConsoleRun;
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

	//return codes
	// 0 = fine
	// 1 = incorrect syntax
	// 2 = custom syntax error
	// 3 = internal error
	//cmds
	static int help(std::vector<std::string> args);
	static int echo(std::vector<std::string> args);
};

struct CommandInfo {
	CommandInfo() : name(""), desc(""), helphint("") {}
	CommandInfo(std::string name, std::string desc, std::string helphint) : name(name), desc(desc), helphint(helphint) {}

	//sorta like sv_cheats
	std::string name;
	//using 'help'
	std::string desc;
	//incorrect syntax
	std::string helphint;
};

class Command
{
	friend class Console;
	friend class ConsoleRun;
public:
	static std::unordered_map<std::string, Command> & create_map()
	{
		static std::unordered_map<std::string, Command> mymap;
		/// init your map here
		return mymap;
	}

	static std::unordered_map<std::string, Command> & get_map()
	{
		static std::unordered_map<std::string, Command> & mymap = create_map(); // this is only called once!
		return mymap; // subsequent calls just return the single instance.
	}

	static void create(int(&handler) (std::vector<std::string> args), const CommandInfo& infoObject);

private:
	int(*m_handler) (std::vector<std::string> args);
	CommandInfo cmdInfo;
	static int currentIndex;
};

//seperate class for runtime
class ConsoleRun
{
friend Console;

private:
	static std::string getLineFromCin();
	//console function
	static int processCommand(std::string input);
	static int run(std::thread& consoleThread, bool& shouldEndThread);
};