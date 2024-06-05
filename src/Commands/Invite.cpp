#include "Command.hpp"

void Command::handleInviteCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
	if (parameters.size() < 2)
	{
		client->GetServer()->clientSendData(client->GetFd(), ERR_NEEDMOREPARAMS(client->GetNickname(), "INVITE"));
		return;
	}
	std::string targetNick = parameters[0];
	std::string channelName = parameters[1];
	IRCChannel* currentChannel = client->GetServer()->GetChannel(channelName);
	if (!currentChannel)
	{
	    client->GetServer()->clientSendData(client->GetFd(), ERR_NOSUCHCHANNEL(client->GetNickname(), channelName));
	    return;
	}
	if (!currentChannel->isMember(client))
	{
	    client->GetServer()->clientSendData(client->GetFd(), ERR_NOTONCHANNEL(client->GetNickname(), channelName));
	    return;
	}
	if (!currentChannel->isOperator(client))
	{
	    client->GetServer()->clientSendData(client->GetFd(), ERR_CHANOPRIVSNEEDED(client->GetNickname(), channelName));
	    return;
	}
	IRCClient* targetClient = client->GetServer()->GetClientByNickname(targetNick);
	if (!targetClient)
	{
	    client->GetServer()->clientSendData(client->GetFd(), ERR_NOSUCHNICK(client->GetNickname(), targetNick));
	    return;
	}
	if (currentChannel->isMember(targetClient))
	{
	    client->GetServer()->clientSendData(client->GetFd(), ERR_USERONCHANNEL(client->GetNickname(), targetNick, channelName));
	    return;
	}
	currentChannel->inviteClient(targetClient);
	client->GetServer()->clientSendData(targetClient->GetFd(), RPL_INVITING(client->GetNickname(), targetNick, channelName));
	client->GetServer()->clientSendData(client->GetFd(), ":" + client->GetNickname() + " INVITE " + targetNick + " :" + channelName);
//	if (targetClient->IsAway())//TODO: HAVE NOT IMPLEMENTED YET
//	{
//	    client->GetServer()->clientSendData(client->GetFd(), RPL_AWAY(client->GetNickname(), targetNick, targetClient->GetAwayMessage()));
//	}
}
