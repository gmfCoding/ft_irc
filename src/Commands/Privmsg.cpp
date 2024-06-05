#include "Command.hpp"

void Command::handlePrivmsgCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    if (parameters.size() < 2)
    {
        client->GetServer()->clientSendData(client->GetFd(), ERR_NORECIPIENT(client->GetNickname(), "PRIVMSG"));
        return ;
    }
    const std::string& receivers = parameters[0];
    const std::string& message = parameters[1];
    if (message.empty())
    {
        client->GetServer()->clientSendData(client->GetFd(), ERR_NOTEXTTOSEND(client->GetNickname()));
        return ;
    }
    std::vector<std::string> receiverList;
    std::stringstream ss(receivers);
    std::string item;
    while (std::getline(ss, item, ','))
        receiverList.push_back(item);
    for (std::vector<std::string>::const_iterator it = receiverList.begin(); it != receiverList.end(); ++it)
    {
        const std::string& receiver = *it;
        if (receiver[0] == '#')
        {
            IRCChannel* channel = client->GetServer()->GetChannel(receiver);
            if (!channel)
            {
                client->GetServer()->clientSendData(client->GetFd(), ERR_NOSUCHCHANNEL(client->GetNickname(), receiver));
                continue;
            }

            if (!channel->canSendMessage(client))
            {
                client->GetServer()->clientSendData(client->GetFd(), ERR_CANNOTSENDTOCHAN(client->GetNickname(), receiver));
                continue;
            }
            channel->broadcast(RPL_PRIVMSG(client->GetNickname(), receiver, message));
        }
        else
        {
            IRCClient* targetClient = client->GetServer()->GetClientByNickname(receiver);
            if (!targetClient)
            {
                client->GetServer()->clientSendData(client->GetFd(), ERR_NOSUCHNICK(client->GetNickname(), receiver));
                continue;
            }
            targetClient->GetServer()->clientSendData(client->GetFd(), RPL_PRIVMSG(client->GetNickname(), receiver, message));
        }
    }
}
