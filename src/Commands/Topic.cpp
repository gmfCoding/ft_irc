#include "Command.hpp"

void Command::handleTopicCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
	if (parameters.empty())
	{
		client->GetServer()->clientSendData(client->GetFd(), ERR_NEEDMOREPARAMS(client->GetNickname(), "TOPIC"));
		return;
	}
	std::string channelName = parameters[0];
	std::string newTopic = (parameters.size() > 1) ? parameters[1] : "";
	IRCChannel* channel = client->GetServer()->GetChannel(channelName);
	if (!channel)
	{
		client->GetServer()->clientSendData(client->GetFd(), ERR_NOSUCHCHANNEL(client->GetNickname(), channelName));
		return;
	}
	 if (!channel->isMember(client))
	{
		client->GetServer()->clientSendData(client->GetFd(), ERR_NOTONCHANNEL(client->GetNickname(), channelName));
		return;
	}
	if (newTopic.empty())
	{
		if (channel->GetTopic().empty())
		{
			client->GetServer()->clientSendData(client->GetFd(), RPL_NOTOPIC(client->GetNickname(), channelName));
		}
		else
		{
			client->GetServer()->clientSendData(client->GetFd(), RPL_TOPIC(client->GetNickname(), channelName, channel->GetTopic()));
		}
	}
	else
	{
		if (channel->isTopicRestricted() && !channel->isOperator(client))
		{
			client->GetServer()->clientSendData(client->GetFd(), ERR_CHANOPRIVSNEEDED(client->GetNickname(), channelName));
			return;
		}
		channel->SetTopic(newTopic);
		channel->broadcast(RPL_TOPIC(client->GetNickname(), channelName, newTopic));
	}
}
