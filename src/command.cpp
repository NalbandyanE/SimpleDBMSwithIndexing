#include "../include/command.h"

#include <sstream>

Command::Command() = default;

Command::Command(const std::string& fullCommand) {
    std::istringstream ss(fullCommand);
    std::string part;
    bool isFirst = true;
    bool inArgument = false;
    bool isParenthesisArgument = false;
    bool isValuesPart = false;
    std::string currentArgument;

    while (ss >> part) {
        if (isFirst) {
            name = part;
            isFirst = false;
        } else {
            if (inArgument) {
                currentArgument += " " + part;
                if (isParenthesisArgument) {
                    if (part.back() == ')') {
                        inArgument = false;
                        isParenthesisArgument = false;
                        currentArgument = currentArgument.substr(1, currentArgument.length() - 2);
                        arguments.push_back(currentArgument);
                    }
                } else {
                    if (part.back() == '\'' || part.back() == '\"') {
                        inArgument = false;
                        currentArgument = currentArgument.substr(1, currentArgument.length() - 2);
                        arguments.push_back(currentArgument);
                    }
                }
            } else {
                if (part.front() == '\'' || part.front() == '\"') {
                    inArgument = true;
                    currentArgument = part;
                    if (part.back() == '\'' || part.back() == '\"') {
                        inArgument = false;
                        currentArgument = currentArgument.substr(1, currentArgument.length() - 2);
                        arguments.push_back(currentArgument);
                    }
                } else if (part.front() == '(') {
                    std::string currentArgument = part;
                    if (part.back() == ')') {
                        arguments.push_back(currentArgument);
                    } else {
                        char c;
                        while (ss.get(c)) {
                            currentArgument += c;
                            if (c == ')') {
                                break;
                            }
                        }
                        arguments.push_back(currentArgument);
                    }
                } else if (part.back() == ';') {
                    part = part.substr(0, part.length() - 1);
                    arguments.push_back(part);
                } else if (part == "DATABASE") {
                    name += " " + part;
                    continue;
                } else if (part == "TABLE") {
                    name += " " + part;
                    continue;
                } else if (part == "INTO") {
                    name += " " + part;
                    continue;
                } else if (part == "VALUES" || part == "values") {
                    continue;
                } else if (part == "FROM") {
                    continue;
                } else if (part == "WHERE") {
                    continue;
                } else if (part == "SET") {
                    continue;
                } else if (part.back() == ',') {
                    part = part.substr(0, part.length() - 1);
                    arguments.push_back(part);
                } else {
                    arguments.push_back(part);
                }
            }
        }
    }
}

std::vector<std::string> Command::splitCommand(const std::string& str, char delimiter) {
    std::vector<std::string> parts;
    std::stringstream ss(str);
    std::string part;
    while (std::getline(ss, part, delimiter)) {
        parts.push_back(part);
    }
    return parts;
}

void Command::setName(const std::string& n) {
    name = n;
}

std::string Command::getName() const {
    return name;
}

void Command::setArguments(const std::vector<std::string>& args) {
    arguments = args;
}

std::vector<std::string> Command::getArguments() const {
    return arguments;
}