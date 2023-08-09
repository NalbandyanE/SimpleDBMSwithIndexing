#ifndef COMMANDVALIDATOR_H
#define COMMANDVALIDATOR_H

#include "command.h"

#include <string>
#include <vector>

class CommandValidator {
public:
    CommandValidator();
    CommandValidator(const Command&);
    bool isValidCommand(const Command&);
    Command getCommand() const;
private:
    Command command;
    std::vector<std::string> validCommands = {
      "CREATE TABLE",
      "CREATE DATABASE",
      "SELECT",
      "INSERT INTO",
      "UPDATE",
      "DELETE"  
    };
};

#endif // COMMANDVALIDATOR_H