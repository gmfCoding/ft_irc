#ifndef COMMANDMODE_HPP
# define COMMANDMODE_HPP

# include "Command.hpp"
# include "IRCClient.hpp"
# include "IRCChannel.hpp"
# include "IRCServer.hpp"
# include <functional>
# include <map>
# include <vector>
# include <string>

class IRCClient;
class IRCChannel;

class CommandMode
{
private:

	typedef		std::map<char, void (*)(IRCChannel*, bool, IRCClient*, const std::vector<std::string>&)> TypeMap_ModeHandlers;
	static TypeMap_ModeHandlers			modeHandlers;
	static void	populateModeHandlers();
	static void	handleInviteOnlyMode(IRCChannel* channel, bool set, IRCClient* client, const std::vector<std::string>& parameters);
	static void	handleTopicRestrictionMode(IRCChannel* channel, bool set, IRCClient* client, const std::vector<std::string>& parameters);
	static void	handleChannelKeyMode(IRCChannel* channel, bool set, IRCClient* client, const std::vector<std::string>& parameters);
	static void	handleOperatorPrivilegeMode(IRCChannel* channel, bool set, IRCClient* client, const std::vector<std::string>& parameters);
	static void	handleUserLimitMode(IRCChannel* channel, bool set, IRCClient* client, const std::vector<std::string>& parameters);

public:
	CommandMode();
	~CommandMode();
	static void handleModeCommand(IRCClient* client, const std::vector<std::string>& parameters);

};

#endif