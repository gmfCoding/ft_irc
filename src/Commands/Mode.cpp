#include "Command.hpp"
#include <unordered_map>
#include <functional>
#include <vector>
#include <string>
#include <iostream>

class IRCClient;
class IRCChannel;

static void handleInviteOnlyMode(IRCChannel* channel, bool set, IRCClient* client, const std::vector<std::string>& parameters);
static void handleTopicRestrictionMode(IRCChannel* channel, bool set, IRCClient* client, const std::vector<std::string>& parameters);
static void handleChannelKeyMode(IRCChannel* channel, bool set, IRCClient* client, const std::vector<std::string>& parameters);
static void handleOperatorPrivilegeMode(IRCChannel* channel, bool set, IRCClient* client, const std::vector<std::string>& parameters);
static void handleUserLimitMode(IRCChannel* channel, bool set, IRCClient* client, const std::vector<std::string>& parameters);

typedef std::unordered_map<char, void (*)(IRCChannel*, bool, IRCClient*, const std::vector<std::string>&)> TypeMap_ModeHandlers;
//typedef std::unordered_map<char, std::function<void(IRCChannel*, bool, IRCClient*, const std::vector<std::string>&)>> TypeMap_ModeHandlers;
//typedef void (*ModeHandler)(IRCChannel*, bool, IRCClient*, const std::vector<std::string>&);
//typedef std::unordered_map<char, ModeHandler> TypeMap_ModeHandlers;

//TypeMap_ModeHandlers modeHandlers = {
//	{'i', handleInviteOnlyMode},
///	{'t', handleTopicRestrictionMode},
//	{'k', handleChannelKeyMode},
//	{'o', handleOperatorPrivilegeMode},
//	{'l', handleUserLimitMode}
//};

TypeMap_ModeHandlers modeHandlers;

void populateModeHandlers()
{
    modeHandlers.insert(std::make_pair('i', handleInviteOnlyMode));
    modeHandlers.insert(std::make_pair('t', handleTopicRestrictionMode));
    modeHandlers.insert(std::make_pair('k', handleChannelKeyMode));
    modeHandlers.insert(std::make_pair('o', handleOperatorPrivilegeMode));
    modeHandlers.insert(std::make_pair('l', handleUserLimitMode));
}

static void handleInviteOnlyMode(IRCChannel* channel, bool set, IRCClient* client, const std::vector<std::string>& parameters)
{
	channel->SetInviteOnly(set);
}

static void handleTopicRestrictionMode(IRCChannel* channel, bool set, IRCClient* client, const std::vector<std::string>& parameters)
{
	channel->SetTopicRestricted(set);
}

static void handleChannelKeyMode(IRCChannel* channel, bool set, IRCClient* client, const std::vector<std::string>& parameters)
{
	if (set)
	{
		if (parameters.size() < 3)
		{
			client->GetServer()->clientSendData(client->GetFd(), ERR_NEEDMOREPARAMS(client->GetNickname(), "MODE"));
			return;
		}
		channel->SetKey(parameters[2]);
	}
	else
		channel->removeKey();
}

static void handleOperatorPrivilegeMode(IRCChannel* channel, bool set, IRCClient* client, const std::vector<std::string>& parameters)
{
	if (parameters.size() < 3)
	{
		client->GetServer()->clientSendData(client->GetFd(), ERR_NEEDMOREPARAMS(client->GetNickname(), "MODE"));
		return;
	}
	IRCClient* targetClient = client->GetServer()->GetClientByNickname(parameters[2]);
	if (set)
		channel->addOperator(targetClient);
	else
		channel->removeOperator(targetClient);
}

static void handleUserLimitMode(IRCChannel* channel, bool set, IRCClient* client, const std::vector<std::string>& parameters)
{
	if (set)
	{
		if (parameters.size() < 3)
		{
			client->GetServer()->clientSendData(client->GetFd(), ERR_NEEDMOREPARAMS(client->GetNickname(), "MODE"));
			return;
		}
		int limit = std::stoi(parameters[2]);
		channel->SetUserLimit(limit);
	}
	else
		channel->removeUserLimit();
}




/*
	handling the modes for oparators i,t,k,o,l we look for a + or a - to determin what we are doing to that mode
	example "-i" would remove invite only, we then use function ptrs to run the correct funtion based on
	the char, it is in a loop coz you should be able to handle multiple at once as it says in the irc bible
*/
void Command::handleModeCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling MODE command" << std::endl;
	populateModeHandlers();//TODO:should setup in constructor
	if (parameters.size() < 2)
	{
		client->GetServer()->clientSendData(client->GetFd(), ERR_NEEDMOREPARAMS(client->GetNickname(), "MODE"));
		return;
	}
	std::string channelName = parameters[0];
	std::string modeString = parameters[1];
	IRCChannel* channel = client->GetServer()->GetChannel(channelName);
	if (!channel)
	{
		client->GetServer()->clientSendData(client->GetFd(), ERR_NOSUCHCHANNEL(client->GetNickname(), channelName));
		return;
	}
	if (!channel->isOperator(client))
	{
		client->GetServer()->clientSendData(client->GetFd(), ERR_CHANOPRIVSNEEDED(client->GetNickname(), channelName));
		return;
	}
	bool set = (modeString[0] == '+');
	for (int i = 1; i < modeString.length(); ++i)
	{
		char mode = modeString[i];
		TypeMap_ModeHandlers::iterator kvp = modeHandlers.find(mode);
		if (kvp != modeHandlers.end())
			kvp->second(channel, set, client, parameters);
		else
		client->GetServer()->clientSendData(client->GetFd(), ERR_UNKNOWNMODE(client->GetNickname(), mode));
	}
}


