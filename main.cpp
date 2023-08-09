#include "include/commandexecutor.h"

#include <iostream>
#include <string>

int main() {
	std::cout << "Welcome to Simple DBMS." << std::endl;
	std::cout << "Enter your SQL command (or 'exit' to quit): \n";
    // std::string input;
    // std::getline(std::cin, input);
    // Command com(input);
    // std::cout << com.getName() << "\n";
    // for (int i = 0; i < com.getArguments().size(); ++i) {
    //     std::cout << com.getArguments()[i] << " ";
    // }
    // std::cout << std::endl;
	CommandExecutor executor;
	while (true) {
		std::string input;
		std::cout << ">>> ";
		std::getline(std::cin, input);
		if (input == "exit") {
			break;
		}
		Command command(input);
		executor.execute(command);
	}

	return 0;
}