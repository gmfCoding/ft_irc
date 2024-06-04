#include "Command.hpp"

void Command::handleQuitCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling QUIT command" << std::endl;
}