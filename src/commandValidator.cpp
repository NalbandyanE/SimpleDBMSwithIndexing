#include "../include/commandValidator.h"

#include <algorithm>

CommandValidator::CommandValidator() = default;

CommandValidator::CommandValidator(const Command& com) : command(com) {}

Command CommandValidator::getCommand() const {
    return command;
}

bool CommandValidator::isValidCommand(const Command& com) {
    std::string commandName = com.getName();
    std::transform(commandName.begin(), commandName.end(), commandName.begin(), ::toupper);
    for (const std::string& validCmd : validCommands) {
        std::string validCmdUpperCase = validCmd;
        std::transform(validCmdUpperCase.begin(), validCmdUpperCase.end(), validCmdUpperCase.begin(), ::toupper);
        if (commandName == validCmdUpperCase) {
            return true;
        }
    }
    return false;
}