#include "Command.hpp"

// TODO: check if the channel name is valid length <= 200)
void Command::handleJoinCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    if (parameters.empty())
    {
        client->GetServer()->clientSendData(client->GetFd(),ERR_NEEDMOREPARAMS(client->GetNickname(),"JOIN"));
        return ;
    }
    std::string channelName = parameters[0];
    std::string key = (parameters.size() > 1) ? parameters[1] : "";
    if (channelName.empty() || (channelName[0] != '&' && channelName[0] != '#'))
    {
        client->GetServer()->clientSendData(client->GetFd(), ERR_NOSUCHCHANNEL(client->GetNickname(), channelName));
        return ;
    }
    IRCChannel* channel = client->GetServer()->GetChannel(channelName);
    if (!channel)
    {
        channel = new IRCChannel(channelName);
        client->GetServer()->addChannel(channel);
        channel->addOperator(client);
    }
    if (channel->isInviteOnly() && !channel->isInvited(client))
    {
        client->GetServer()->clientSendData(client->GetFd(), ERR_INVITEONLYCHAN(client->GetNickname(), channelName));
        return ;
    }
    if (channel->isBanned(client))
    {
        client->GetServer()->clientSendData(client->GetFd(), ERR_BANNEDFROMCHAN(client->GetNickname(), channelName));
        return ;
    }
    if (channel->hasKey() && channel->GetKey() != key)
    {
        client->GetServer()->clientSendData(client->GetFd(), ERR_BADCHANNELKEY(client->GetNickname(), channelName));
        return ;
    }
    if (channel->isFull())
    {
        client->GetServer()->clientSendData(client->GetFd(), ERR_CHANNELISFULL(client->GetNickname(), channelName));
        return ;
    }
    channel->addMember(client);
    channel->broadcast(RPL_JOIN(client->GetNickname(), channelName));
    if (!channel->GetTopic().empty())
    {
        client->GetServer()->clientSendData(client->GetFd(), RPL_TOPIC(client->GetNickname(), channelName, channel->GetTopic()));
    }
    client->GetServer()->clientSendData(client->GetFd(), RPL_NAMREPLY(client->GetNickname(), channelName, channel->GetMemberList()));
    client->GetServer()->clientSendData(client->GetFd(), RPL_ENDOFNAMES(client->GetNickname(), channelName));
}
