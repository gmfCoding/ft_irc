#ifndef COMMAND_HPP
# define COMMAND_HPP
# include <vector>
# include <functional>
# include "IRCRespondMacros.hpp"
# include "AuthLevel.hpp"
# include "IRCClient.hpp"


//class IRCServer;
class IRCClient;
class IRCChannel;

class Command
{
private:
    std::string name;                // Command name
    AuthLevel minAuthLevel;          // Minimum required authority level
    std::function<void(IRCClient*, const std::vector<std::string>&)> function;
public:
    Command(const std::string& name, AuthLevel level, std::function<void(IRCClient*, const std::vector<std::string>&)> func);
    ~Command();
    const std::string&  GetName() const;
    AuthLevel           GetAuthLevel() const;
    void                execute(IRCClient* client, const std::vector<std::string>& params) const;
    static void         handleNickCommand(IRCClient* client, const std::vector<std::string>& parameters);
    static void         handleUserCommand(IRCClient* client, const std::vector<std::string>& parameters);
    static void			handlePassCommand(IRCClient* client, const std::vector<std::string>& parameters);
	static void			handleJoinCommand(IRCClient* client, const std::vector<std::string>& parameters);
	static void			handlePrivmsgCommand(IRCClient* client, const std::vector<std::string>& parameters);
	static void			handleQuitCommand(IRCClient* client, const std::vector<std::string>& parameters);
	static void			handleModeCommand(IRCClient* client, const std::vector<std::string>& parameters);
	static void			handleTopicCommand(IRCClient* client, const std::vector<std::string>& parameters);
	static void			handleInviteCommand(IRCClient* client, const std::vector<std::string>& parameters);
	static void			handleKickCommand(IRCClient* client, const std::vector<std::string>& parameters);
    static void			handlePartCommand(IRCClient* client, const std::vector<std::string>& parameters);

};




// add other command classes here...

#endif