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
/*#include <iostream>
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
}*/
#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <map>

struct command_processor
{
	// http://en.cppreference.com/w/cpp/utility/functional/function
	using command = std::function< void(std::vector<std::string> args) >;

	std::map< std::string, command > commands;

	void execute(const std::string& cmd_name, std::vector<std::string> args = {}) const
	{
		std::cout << "\nexecute command '" << cmd_name << "' => ";
		const auto iter = commands.find(cmd_name);
		if (iter != commands.end()) iter->second(std::move(args));
	}

	void list() const
	{
		std::cout << "list of commands\n------------\n";
		for (const auto& pair : commands) std::cout << "    " << pair.first << '\n';
	}
};

int main()
{
	struct A
	{
		int d = 0;
		void do_it(std::vector<std::string> args) const
		{
			std::cout << "main::A::do_it called with args: ";
			for (const auto& a : args) std::cout << a << ' ';
			std::cout << '\n';
			std::cout << d << std::endl;
		}
	};

	A a;

	command_processor cp
	{ {
			// http://en.cppreference.com/w/cpp/utility/functional/bind
		{ "do_it", std::bind(&A::do_it, std::addressof(a), std::placeholders::_1) },
	{ "say_hello" , [](auto) { std::cout << "hello from a closure object\n"; } }
		} };

	cp.commands.emplace("another_command", [](auto) { std::cout << "another command\n"; });

	cp.list();

	cp.execute("do_it", { "one", "two", "three" });
	cp.execute("say_hello");
	std::string b;
	std::getline(std::cin, b);
}