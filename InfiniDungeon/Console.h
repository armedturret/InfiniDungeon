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
	static int spliceargs(std::vector<std::string> args);
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

inline int defaultOnChange(std::string newvalue) {
	//return 1 to reject new value
	return 0;
}

struct CVar {

	CVar() : text(""), valType(""), val(""), m_onchange(defaultOnChange) {}
	CVar(std::string text, std::string valType, std::string val) : text(text), valType(valType), val(val), m_onchange(defaultOnChange) {}
	CVar(std::string text, std::string valType, std::string val, int(&onchange) (std::string newvalue)) : text(text), valType(valType), val(val), m_onchange(onchange) {}
	std::string text;
	//what type to run
	std::string valType;
	std::string val;
	int(*m_onchange) (std::string newvalue);
};

class Command
{
	friend class Console;
	friend class ConsoleRun;
public:
	std::string getCvar(std::string name);

	static std::unordered_map<std::string, Command> & create_map()
	{
		static std::unordered_map<std::string, Command> mymap;
		// init your map here
		return mymap;
	}

	static std::unordered_map<std::string, Command> & get_map()
	{
		static std::unordered_map<std::string, Command> & mymap = create_map(); // this is only called once!
		return mymap; // subsequent calls just return the single instance.
	}

	static std::unordered_map<std::string, CVar> & create_vap()
	{
		static std::unordered_map<std::string, CVar> myvap;
		// init your map here
		return myvap;
	}

	static std::unordered_map<std::string, CVar> & get_vap()
	{
		static std::unordered_map<std::string, CVar> & myvap = create_vap(); // this is only called once!
		return myvap; // subsequent calls just return the single instance.
	}


	static void create(int(&handler) (std::vector<std::string> args), const CommandInfo& infoObject);
	static void createCVar(const CVar& varObject);
private:
	int(*m_handler) (std::vector<std::string> args);
	CommandInfo cmdInfo;
	static int currentIndex;
};

inline bool is_digits(const std::string &str)
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}

//seperate class for runtime
class ConsoleRun
{
friend Console;
private:
	static std::string getLineFromCin();
	//console function
	static int processCvar(CVar& cvar, const std::string& val);
	static int processCommand(const std::string& input);
	static int run(std::thread& consoleThread, bool& shouldEndThread);
};