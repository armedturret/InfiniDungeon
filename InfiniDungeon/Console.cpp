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

std::shared_ptr<GameplayScreen> Console::theScreen = nullptr;

void Console::init()
{
	Command::create_map();
	Command::create_vap();

	//make commands
	Command::create(Console::help, CommandInfo("help", "Lists all commands.", "help OR help <command||cvar> OR help cvar"));
	Command::create(Console::echo, CommandInfo("echo", "Prints text that follows.", "echo <words..>"));
	Command::create(Console::quit, CommandInfo("quit","Quits the game.","quit"));

	//game commands
	Command::create(Console::listCreatures, CommandInfo("infi_listcreatures", "List all currently active creatures.", "infi_listcreatures"));
	Command::create(Console::getCreatureInfo, CommandInfo("infi_getcreaturestats", "Gets info of specified creature.", "infi_getcreatureinfo <creatureid>"));
	Command::create(Console::testDamage, CommandInfo("infi_test_damage", "Test the damage between two creatures.", "infi_test_damage <defenderid> <attackerid> OR infi_test_damage <defenderarmour> <defenderevade> <attackdamage> <attackerevade>"));

#ifdef _DEBUG
	//debug commands (start with db_)
	Command::create(Console::spliceargs, CommandInfo("db_spliceargs", "Debug operation to show how arguments would be spliced","db_spliceargs <args..>"));
#endif
	//make unsafecvars (don't run from console)
	Command::createCVar(CVar("infi_unsafecvar_safetorun", "int", "0"));
	Command::createCVar(CVar("infi_shouldquit", "int", "0"));
}

void Console::run(std::shared_ptr<GameplayScreen> screen) {
	theScreen = screen;

	m_shouldEndThread = false;
	console = std::thread(ConsoleRun::run, std::ref(console), std::ref(m_shouldEndThread));
	std::cout << "Console thread initialized; Id: " << console.get_id() << std::endl;
	std::cout << "Note that modifying and running some of the commands can really mess up the game/computer\nUSE AT YOUR OWN RISK (know what you're doing)" << std::endl;
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
	if (args.size() > 1) {
		auto dit = Command::get_map().find(args[1]);
		if (dit == Command::get_map().end()) {
			//check if cvar
			auto vit = Command::get_vap().find(args[1]);
			if (vit == Command::get_vap().end()) {
				if (args[1] == "cvar") {
					for (auto crit = Command::get_vap().begin(); crit != Command::get_vap().end(); crit++) {
						std::cout << "[help]: " << crit->second.text << " = " << crit->second.val << std::endl;
					}
				}
				else {
					std::cout << "[help]: That is not a recognized command or cvar.\n[urdumb]: Use 'help' for a list of commands and help cvars for a list of cvars." << std::endl;
					return 1;
				}
				return 0;
			}
			else {
				std::cout << "[help]: " << vit->second.text << " = " << vit->second.val << std::endl;
			}
		}
		else {
			Command target = dit->second;
			std::cout << "[help]: " << target.cmdInfo.name << " - " << target.cmdInfo.desc << std::endl;
			std::cout << "[help]: SYNTAX: " << target.cmdInfo.helphint << std::endl;
		}
	}
	else {
		for (auto it = Command::get_map().begin(); it != Command::get_map().end(); it++) {
			std::cout << "[help]: " << it->second.cmdInfo.name << " - " << it->second.cmdInfo.desc << std::endl;
		}
	}
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

int Console::spliceargs(std::vector<std::string> args)
{
	for (int s = 0; s < args.size(); s++) {
		std::cout << "[spliceargs]: " << s << " = " << args[s] << std::endl;
	}
	return 0;
}

int Console::listCreatures(std::vector<std::string> args)
{
	if (Command::getCvar("infi_unsafecvar_safetorun") == "1") {
		return theScreen->getCreatures(args);
	}
	else {
		std::cout << "[infi]: Cannot run game specific commands prior to initialization." << std::endl;
		return 3;
	}
}

int Console::getCreatureInfo(std::vector<std::string> args)
{
	if (Command::getCvar("infi_unsafecvar_safetorun") == "1") {
		return theScreen->getCreatureStats(args);
	}
	else {
		std::cout << "[infi]: Cannot run game specific commands prior to initialization." << std::endl;
		return 3;
	}
}

int Console::testDamage(std::vector<std::string> args)
{
	if (Command::getCvar("infi_unsafecvar_safetorun") == "1") {
		return theScreen->testDamage(args);
	}
	else {
		std::cout << "[infi]: Cannot run game specific commands prior to initialization." << std::endl;
		return 3;
	}
	return 0;
}

int Console::quit(std::vector<std::string> args)
{
	Command::setCvar("infi_shouldquit", "1");
	return 0;
}

std::string Command::getCvar(std::string name)
{
	auto vit = Command::get_vap().find(name);
	if (vit != Command::get_vap().end()) {
		return vit->second.val;
	}
	else {
		std::cout << "[cvar]: Attempted access to unknown cvar \'" << name << "\'." << std::endl;
	}
	return "UNKNOWN VALUE";
}

int Command::setCvar(std::string name, std::string val)
{
	CVar *cvar;
	auto vit = Command::get_vap().find(name);
	if (vit != Command::get_vap().end()) {
		cvar = &vit->second;
	}
	else {
		std::cout << "[cvar]: Attempted access to unknown cvar \'" << name << "\'." << std::endl;
		return 1;
	}
	if (cvar->valType == "int") {
		if (is_digits(val)) {
			if (!cvar->m_onchange(val))
				cvar->val = val;
		}
		else {
			std::cout << "[cvar]: Incorrect data type." << std::endl;
			return 1;
		}
		return 0;
	}
	else if (cvar->valType == "string") {
		if (!cvar->m_onchange(val))
			cvar->val = val;
		return 0;
	}
	else {
		std::cout << "[cvar]: cvar " << cvar->text << " has unknown type. Please report this to the developer." << std::endl;
		return 1;
	}
	return 1;
}

std::string ConsoleRun::getLineFromCin()
{
	std::string line;
	std::getline(std::cin, line);
	return line;
}

int ConsoleRun::processCvar(CVar& cvar, const std::string& val)
{
	if (cvar.valType == "int") {
		if (is_digits(val)) {
			if(!cvar.m_onchange(val))
				cvar.val = val;
		}
		else {
			std::cout << "[cvar]: Incorrect data type." << std::endl;
			return 1;
		}
		return 0;
	}
	else if (cvar.valType == "string") {
		if (!cvar.m_onchange(val))
			cvar.val = val;
		return 0;
	}
	else {
		std::cout << "[cvar]: cvar " << cvar.text << " has unknown type. Please report this to the developer." << std::endl;
	}
	return 1;
}

int ConsoleRun::processCommand(const std::string& input)
{
	std::istringstream iss(input);
	std::vector<std::string> rawargs{ std::istream_iterator<std::string>{iss},
		std::istream_iterator<std::string>{} };

	std::vector<std::string> tokens;

	bool begunstring = false;
	int compensation = 0;
	//parse if strings
	for (int i = 0; i < rawargs.size(); i++) {
		if (rawargs[i].substr(0, 1) == "\"" && !begunstring) {
			begunstring = true;
			if (rawargs[i].substr(rawargs[i].size()-1) == "\"" && (rawargs[i].size() - 2 >= 0 && rawargs[i].substr(rawargs[i].size() - 2,1) != "\\")) {
				if (rawargs[i].size() - 2 > 0) {
					tokens.push_back(rawargs[i].substr(1, rawargs[i].size() - 2));
					begunstring = false;
				}else{
					tokens.push_back("");
					begunstring = false;
				}
			}
			else {
				if (rawargs[i].size() > 0) {
					tokens.push_back(rawargs[i].substr(1));
					compensation += 1;
				}
				else {
					tokens.push_back(" ");
					compensation += 1;
				}
			}
			
		}
		else {
			if (begunstring) {
				if (rawargs[i].substr(rawargs[i].size() - 1) == "\"" && (rawargs[i].size() - 2 >= 0 && rawargs[i].substr(rawargs[i].size() - 2,1) != "\\")) {
					begunstring = false;
					tokens[i - compensation] += " ";
					if(rawargs[i].size() > 1)
						tokens[i-compensation] += rawargs[i].substr(0, rawargs[i].size() - 1);
					else {
						tokens[i - compensation] += "";
					}
				}
				else {
					tokens[i - compensation] += " ";
					tokens[i - compensation] += rawargs[i];
					compensation += 1;
				}
				
			}
			else {
				if (rawargs[i].substr(rawargs[i].size() - 1) == "\"" && (rawargs[i].size() - 2 >= 0 && rawargs[i].substr(rawargs[i].size() - 2, 1) != "\\")) {
					std::cout << "[urdumb]: String is not started!" << std::endl;
					return 1;
				}

				tokens.push_back(rawargs[i]);
			}
		}
	}

	//throw errors after pre command processing
	if (begunstring) {
		std::cout << "[urdumb]: String is not terminated!" << std::endl;
		return 1;
	}
	
	//check for lone wolf quotes
	for (int i = 0; i < tokens.size(); i++) {
		std::string*s = &tokens[i];
		std::size_t result = -1;
		while (true) {
			//search for '\'
			result = s->find('\"', result + 1);
			if (result != std::string::npos) {
				if (result == 0) {
					std::cout << "[urdumb]: There was a lone quote in your arguments." << std::endl;
					return 1;
				}else if (s[0][result - 1] != '\\') {
					std::cout << "[urdumb]: There was a lone quote in your arguments." << std::endl;
					return 1;
				}
			}
			else {
				break;
			}
		}
	}
	//check escape sequences
	for (int i = 0; i < tokens.size(); i++) {
		std::string*s = &tokens[i];
		std::size_t result = -1;
		while(true){
			//search for '\'
			result = s->find('\\',result+1);
			if (result != std::string::npos || result == s->length() - 1) {
				//check if its lonely
				if (s[0][result + 1] == '\\') {
					s->erase(s->begin() + result + 1);
				}
				else if (s[0][result + 1] == '"') {
					s->erase(s->begin() + result);
				}
				else if (s[0][result + 1] == '\'') {
					s->erase(s->begin() + result);
				}
				else {
					std::cout << "[urdumb]: There was an unrecognized backslash in your arguments." << std::endl;
					return 1;
				}
			}
			else {
				if (result == s->length() - 1) {
					std::cout << "[urdumb]: There was an unrecognized backslash in your arguments." << std::endl;
					return 1;
				}
				break;
			}
		}
	}

	if (tokens.size() > 0) {
		auto it = Command::get_map().find(tokens[0]);
		if (it == Command::get_map().end()) {
			//check if cvar
			auto vit = Command::get_vap().find(tokens[0]);
			if (vit == Command::get_vap().end()) {
				std::cout << "[urdumb]: That is not a recognized command or cvar.\n[urdumb]: Use 'help' for a list of commands and help cvars for a list of cvars." << std::endl;
				return 1;
			}
			else {
				if (tokens.size() > 1) {
					processCvar(vit->second, tokens[1]);
				}
				else {
					std::cout << "[cvar]: " << vit->second.text << " = " << vit->second.val << std::endl;
				}
			}
			return 0;
		}
		else {
			Command cmd = it->second;
			int err = cmd.m_handler(tokens);
			if (err == 1) {
				std::cout << "[urdumb]: "<<cmd.cmdInfo.helphint << std::endl;
			}
			else {
				return err;
			}
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

void Command::createCVar(const CVar & varObject)
{
	Command::get_vap().insert(std::make_pair(varObject.text, varObject));
}
