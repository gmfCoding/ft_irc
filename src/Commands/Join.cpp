#include "Command.hpp"

// TODO: check if the channel name is valid length <= 200)
void Command::handleJoinCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
	if (parameters.empty())
	{
		client->GetServer()->clientSendData(client->GetFd(),ERR_NEEDMOREPARAMS(client->GetNickname(),"JOIN"));
		return ;
	}
	std::vector<std::string> channels = splitString(parameters[0], ',');
	std::vector<std::string> keys;
	if (parameters.size() > 1)
		keys = splitString(parameters[1], ',');
	for (size_t i = 0; i < channels.size(); ++i)
	{
		std::string channelName = channels[i];
		std::string key = (i < keys.size()) ? keys[i] : "";
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
		if (channel->GetUserLimit() != 0 && channel->isFull())
		{
			client->GetServer()->clientSendData(client->GetFd(), ERR_CHANNELISFULL(client->GetNickname(), channelName));
			return ;
		}
		channel->addMember(client);
		channel->broadcast(RPL_JOIN(client->GetHostname(), channelName));
		if (!channel->GetTopic().empty())
			client->GetServer()->clientSendData(client->GetFd(), RPL_TOPIC(client->GetNickname(), channelName, channel->GetTopic()));
		else
			client->GetServer()->clientSendData(client->GetFd(), RPL_NOTOPIC(client->GetNickname(), channelName));
		client->GetServer()->clientSendData(client->GetFd(), RPL_NAMREPLY(client->GetNickname(), channelName, channel->GetMemberList()));
		client->GetServer()->clientSendData(client->GetFd(), RPL_ENDOFNAMES(client->GetNickname(), channelName));
	}
}
