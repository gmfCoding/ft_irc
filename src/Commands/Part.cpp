#include "Command.hpp"

void Command::handlePartCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
	if (parameters.empty())
	{
	    client->GetServer()->clientSendData(client->GetFd(), ERR_NEEDMOREPARAMS(client->GetNickname(), "PART"));
	    return;
	}
	std::string channelName = parameters[0];
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
	channel->removeMember(client);
	client->SetCurrentChannel(nullptr);
	std::string partMessage = ":" + client->GetNickname() + " PART " + channelName;
	channel->broadcast(partMessage);
	client->GetServer()->clientSendData(client->GetFd(), partMessage);
	
//	if (channel->GetMemberList().empty())//TODO: make decision if the channel is removed when there are no more members left
//	{
//	    client->GetServer()->removeChannel(channelName);//need to add a removeChannel fucntion
//	    delete channel;
//	}
}