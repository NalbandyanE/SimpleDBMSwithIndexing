#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

class Command {
public:
    Command();
    Command(const std::string&);
    void setName(const std::string&);
    std::string getName() const;
    void setArguments(const std::vector<std::string>&);
    std::vector<std::string> getArguments() const;
	std::vector<std::string> splitCommand(const std::string&, char);
private:
    std::string name;
    std::vector<std::string> arguments;
};

#endif // COMMAND_H