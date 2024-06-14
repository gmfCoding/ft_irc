#include "Command.hpp"

Command::Command(const std::string& name, AuthLevel level, std::function<void(IRCClient*, const std::vector<std::string>&)> func)
        : name(name), minAuthLevel(level), function(func) {}
Command::~Command() { return ; }

const std::string&			Command::GetName() const { return name; }
AuthLevel					Command::GetAuthLevel() const { return minAuthLevel; }
void						Command::execute(IRCClient* client, const std::vector<std::string>& params) const { function(client, params); }
void						Command::handleModeCommand(IRCClient* client, const std::vector<std::string>& parameters) { commandMode.handleModeCommand(client, parameters); }

std::vector<std::string>	Command::splitChannels(const std::string& channelList)
{
    std::vector<std::string> channels;
    std::stringstream ss(channelList);
    std::string channel;
    while (std::getline(ss, channel, ','))
	{
        if (!channel.empty())
            channels.push_back(channel);
    }
    return (channels);
}
