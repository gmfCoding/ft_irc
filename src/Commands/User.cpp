#include "Command.hpp"


void Command::handleUserCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling USER command" << std::endl;
    if (parameters.size() < 4) {
        client->GetServer()->clientSendData(client->GetFd(), ERR_NEEDMOREPARAMS(client->GetNickname(), "USER"));
        return;
    }
    std::string username = parameters[0];
    std::string hostname = parameters[1];
    std::string servername = parameters[2];
    std::string realname = parameters[3];
    client->SetUsername(username);
    client->SetRealname(realname);
    client->SetAuthStatus(USER, true); 
}