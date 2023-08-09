#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H

#include "commandvalidator.h"
#include "dbms.h"

class CommandExecutor {
public:
	CommandExecutor();
	CommandExecutor(const Command&);
	void execute(const Command&);
private:
	Command command;
    DBMS db;
	Table table;
    std::vector<std::string> splitValues(const std::string& values);
    std::vector<std::string> splitCommand(const std::string& str, char delimiter);
};

#endif // COMMANDEXECUTOR_H