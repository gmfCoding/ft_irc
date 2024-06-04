#include "Command.hpp"

void Command::handleKickCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling KICK command" << std::endl;
    if (parameters.size() < 2)
        return ;
    std::string channelName = parameters[0];
    std::string targetNick = parameters[1];

}