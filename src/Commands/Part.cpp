#include "Command.hpp"

void Command::handlePartCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    if (parameters.empty())
    {
        // send error message to client about missing channel name
        return ;
    }
}