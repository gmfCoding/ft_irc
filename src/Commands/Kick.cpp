#include "Command.hpp"

void Command::handleKickCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
	if (parameters.size() < 2)
	{
		client->GetServer()->clientSendData(client->GetFd(), ERR_NEEDMOREPARAMS(client->GetNickname(), "KICK"));
		return ;
	}
	std::string channelName = parameters[0];
	std::string targetNick = parameters[1];
	std::string reason = (parameters.size() > 2) ? parameters[2] : "No reason";
	IRCChannel* channel = client->GetServer()->GetChannel(channelName);
	if (!channel)
	{
		client->GetServer()->clientSendData(client->GetFd(), ERR_NOSUCHCHANNEL(client->GetNickname(), channelName));
		return ;
	}
	if (!channel->isMember(client))
	{
		client->GetServer()->clientSendData(client->GetFd(), ERR_NOTONCHANNEL(client->GetNickname(), channelName));
		return ;
	}
	if (!channel->isOperator(client))
	{
		client->GetServer()->clientSendData(client->GetFd(), ERR_CHANOPRIVSNEEDED(client->GetNickname(), channelName));
		return ;
	}
	IRCClient* targetClient = client->GetServer()->GetClientByNickname(targetNick);
	if (!targetClient || !channel->isMember(targetClient))
	{
		client->GetServer()->clientSendData(client->GetFd(), ERR_USERNOTINCHANNEL(client->GetNickname(), targetNick, channelName));
		return ;
	}
	channel->broadcast(RPL_KICK(client->GetNickname(), channelName, targetNick, reason));
	channel->removeMember(targetClient);
}