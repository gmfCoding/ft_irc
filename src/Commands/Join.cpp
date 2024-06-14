#include "Command.hpp"



std::vector<std::string> splitString(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    
    // Ensure trailing empty segments are captured
    if (str.back() == delimiter)
        tokens.push_back("");
    
    return tokens;
}


// TODO: check if the channel name is valid length <= 200)
void Command::handleJoinCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
	if (parameters.empty())
	{
		client->GetServer()->clientSendData(client->GetFd(),ERR_NEEDMOREPARAMS(client->GetNickname(),"JOIN"));
		return ;
	}
	std::vector<std::string> channels = splitChannels(parameters[0]);
    std::vector<std::string> keys;
    if (parameters.size() > 1)
        keys = splitString(parameters[1], ',');
	std::cout << "Channels: ";
    for (const auto& channel : channels)
        std::cout << channel << ".. ";
    std::cout << "\nKeys: ";
    for (const auto& key : keys)
        std::cout << key << ".. ";
    std::cout << std::endl;
    for (size_t i = 0; i < channels.size(); ++i)
	{
        std::string channelName = channels[i];
        std::string key = (i < keys.size()) ? keys[i] : "";
		std::cout << channelName << "and the key = " << key << std::endl;
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
			std::cout << "WEHAVE USER LIMIT" << std::endl;
			client->GetServer()->clientSendData(client->GetFd(), ERR_CHANNELISFULL(client->GetNickname(), channelName));
			return ;
		}
		channel->addMember(client);
		client->SetCurrentChannel(channel);
		channel->broadcast(RPL_JOIN(client->GetHostname(), channelName));
		if (!channel->GetTopic().empty())
			client->GetServer()->clientSendData(client->GetFd(), RPL_TOPIC(client->GetNickname(), channelName, channel->GetTopic()));
		else
			client->GetServer()->clientSendData(client->GetFd(), RPL_NOTOPIC(client->GetNickname(), channelName));
		client->GetServer()->clientSendData(client->GetFd(), RPL_NAMREPLY(client->GetNickname(), channelName, channel->GetMemberList()));
		client->GetServer()->clientSendData(client->GetFd(), RPL_ENDOFNAMES(client->GetNickname(), channelName));
	}
}
