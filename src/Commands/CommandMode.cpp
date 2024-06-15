#include "CommandMode.hpp"

CommandMode::TypeMap_ModeHandlers CommandMode::modeHandlers;

CommandMode::CommandMode()
{
	populateModeHandlers();
}

void CommandMode::populateModeHandlers()
{
	modeHandlers.insert(std::make_pair('i', handleInviteOnlyMode));
	modeHandlers.insert(std::make_pair('t', handleTopicRestrictionMode));
	modeHandlers.insert(std::make_pair('k', handleChannelKeyMode));
	modeHandlers.insert(std::make_pair('o', handleOperatorPrivilegeMode));
	modeHandlers.insert(std::make_pair('l', handleUserLimitMode));
}

CommandMode::~CommandMode()
{
	return ;
}

void	CommandMode::handleInviteOnlyMode(IRCChannel* channel, bool set, IRCClient* client, const std::vector<std::string>& parameters)
{
	channel->SetInviteOnly(set);
	if (set)
		channel->broadcast(RPL_MODE(client->GetNickname(), channel->GetName(), "+i", ""));
	else
		channel->broadcast(RPL_MODE(client->GetNickname(), channel->GetName(), "-i", ""));
}

void	CommandMode::handleTopicRestrictionMode(IRCChannel* channel, bool set, IRCClient* client, const std::vector<std::string>& parameters)
{
	channel->SetTopicRestricted(set);
	if (set)
		channel->broadcast(RPL_MODE(client->GetNickname(), channel->GetName(), "+t", ""));
	else
		channel->broadcast(RPL_MODE(client->GetNickname(), channel->GetName(), "-t", ""));
}

void	CommandMode::handleChannelKeyMode(IRCChannel* channel, bool set, IRCClient* client, const std::vector<std::string>& parameters)
{
	if (set)
	{
		if (parameters.empty())
		{
			client->GetServer()->clientSendData(client->GetFd(), ERR_NEEDMOREPARAMS(client->GetNickname(), "MODE"));
			return;
		}
		channel->SetKey(parameters[0]);
		channel->broadcast(RPL_MODE(client->GetNickname(), channel->GetName(), "+k", parameters[0]));
	}
	else
	{
		channel->removeKey();
		channel->broadcast(RPL_MODE(client->GetNickname(), channel->GetName(), "-k", ""));
	}
}

void	CommandMode::handleOperatorPrivilegeMode(IRCChannel* channel, bool set, IRCClient* client, const std::vector<std::string>& parameters)
{
	if (parameters.empty())
	{
		client->GetServer()->clientSendData(client->GetFd(), ERR_NEEDMOREPARAMS(client->GetNickname(), "MODE"));
		return;
	}
	IRCClient* targetClient = client->GetServer()->GetClientByNickname(parameters[0]);
	if (set)
	{
		channel->addOperator(targetClient);
		channel->broadcast(RPL_MODE_ADD_OPERATOR(client->GetNickname(), channel->GetName(), targetClient->GetNickname()));
	}
	else
	{
		channel->removeOperator(targetClient);
		channel->broadcast(RPL_MODE_REMOVE_OPERATOR(client->GetNickname(), channel->GetName(), targetClient->GetNickname()));
	}
}

void	CommandMode::handleUserLimitMode(IRCChannel* channel, bool set, IRCClient* client, const std::vector<std::string>& parameters)
{
	if (set)
	{
		if (parameters.empty())
		{
			client->GetServer()->clientSendData(client->GetFd(), ERR_NEEDMOREPARAMS(client->GetNickname(), "MODE"));
			return;
		}
		int limit = std::stoi(parameters[0]);
		channel->SetUserLimit(limit);
		channel->broadcast(RPL_MODE(client->GetNickname(), channel->GetName(), "+l", parameters[0]));
	}
	else
	{
		channel->removeUserLimit();
		channel->broadcast(RPL_MODE(client->GetNickname(), channel->GetName(), "-l", ""));
	}
}


/*
	handling the modes for oparators i,t,k,o,l we look for a + or a - to determin what we are doing to that mode
	example "-i" would remove invite only, we then use function ptrs to run the correct funtion based on
	the char, it is in a loop coz you should be able to handle multiple at once as it says in the irc bible
*/
void	CommandMode::handleModeCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
	if (parameters.size() < 2)
	{
		client->GetServer()->clientSendData(client->GetFd(), ERR_NEEDMOREPARAMS(client->GetNickname(), "MODE"));
		return ;
	}
	std::string channelName = parameters[0];
	std::string modeString = parameters[1];
	IRCChannel* channel = client->GetServer()->GetChannel(channelName);
	if (!channel)
	{
		client->GetServer()->clientSendData(client->GetFd(), ERR_NOSUCHCHANNEL(client->GetNickname(), channelName));
		return ;
	}
	if (!channel->isOperator(client))
	{
		client->GetServer()->clientSendData(client->GetFd(), ERR_CHANOPRIVSNEEDED(client->GetNickname(), channelName));
		return ;
	}
	bool set = true;
	int parameterIndex = 2;
	for (int i = 0; i < modeString.length(); ++i)
	{
		char mode = modeString[i];
		if (mode == '+')
			set = true;
		else if (mode == '-')
			set = false;
		else
		{
			TypeMap_ModeHandlers::iterator kvp = modeHandlers.find(mode);
			if (kvp != modeHandlers.end())
			{
				std::vector<std::string> modeParameters;
				if (mode == 'k' || mode == 'l' || mode == 'o')//if we add more operator modes that take parameters add them here too
				{
					if (parameterIndex < parameters.size())
					{
						modeParameters.push_back(parameters[parameterIndex]);
						parameterIndex++;
					}
					else
					{
						client->GetServer()->clientSendData(client->GetFd(), ERR_NEEDMOREPARAMS(client->GetNickname(), "MODE"));
						return ;
					}
				}
				kvp->second(channel, set, client, modeParameters);
			}
			else
				client->GetServer()->clientSendData(client->GetFd(), ERR_UNKNOWNMODE(client->GetNickname(), mode));
		}
	}
}
