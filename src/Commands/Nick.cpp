#include "Command.hpp"


void Command::handleNickCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling NICK command" << std::endl;
    std::string newNickname = parameters[0];
    client->SetNickname(newNickname);
}