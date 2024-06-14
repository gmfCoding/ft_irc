#include "Command.hpp"


void Command::handleNickCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling NICK command" << std::endl;
    if (parameters.empty())
    {
        client->GetServer()->clientSendData(client->GetFd(), ERR_NONICKNAMEGIVEN(client->GetNickname()));
        return;
    }
    std::string newNickname = parameters[0];
    if (client->GetServer()->isNicknameInUse(newNickname))
    {
        client->GetServer()->clientSendData(client->GetFd(), ERR_NICKNAMEINUSE(client->GetNickname(), newNickname));
        return;
    }
    client->SetNickname(newNickname);
    client->SetAuthStatus(NICK, true);
}
