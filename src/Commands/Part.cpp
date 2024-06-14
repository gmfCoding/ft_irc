#include "Command.hpp"

void Command::handlePartCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
	if (parameters.empty())
	{
	    client->GetServer()->clientSendData(client->GetFd(), ERR_NEEDMOREPARAMS(client->GetNickname(), "PART"));
	    return;
	}
	std::vector<std::string> channels = splitChannels(parameters[0]);
    for (const std::string& channelName : channels)
    {
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
		channel->broadcast(RPL_PART(client->GetNickname(), channelName));
		channel->removeMember(client);
		client->SetCurrentChannel(nullptr);
//		if (channel->GetMemberList().empty())//TODO: make decision if the channel is removed when there are no more members left
//		{
//		    client->GetServer()->removeChannel(channelName);//need to add a removeChannel fucntion
//		    delete channel;
//		}
	}
}