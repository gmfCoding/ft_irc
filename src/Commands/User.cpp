#include "Command.hpp"


void Command::handleUserCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling USER command" << std::endl;
    std::string username = parameters[0];
    client->SetUsername(username);
}