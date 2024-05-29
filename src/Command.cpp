#include "Command.hpp"

Command::Command(const std::string& name, AuthLevel level, std::function<void(IRCClient*, const std::vector<std::string>&)> func)
        : name(name), minAuthLevel(level), function(func) 
{
    return ;
}

Command::~Command() { return ; }
const std::string&  Command::GetName() const { return name; }
AuthLevel           Command::GetAuthLevel() const { return minAuthLevel; }

void Command::execute(IRCClient* client, const std::vector<std::string>& params) const { function(client, params); }

void Command::handleNickCommand(IRCClient* client, const std::vector<std::string>& parameters)
{

    std::string newNickname = parameters[0];
    client->SetNickname(newNickname);
}

void Command::handleUserCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::string username = parameters[0];
    client->SetUsername(username);
}

void Command::handlePassCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling PASS command" << std::endl;
}

void Command::handleJoinCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling JOIN command" << std::endl;
}

void Command::handlePrivmsgCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling PRIVMSG command" << std::endl;
}

void Command::handleQuitCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling QUIT command" << std::endl;
}

void Command::handleModeCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling MODE command" << std::endl;
}

void Command::handleTopicCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling TOPIC command" << std::endl;
}

void Command::handleInviteCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling INVITE command" << std::endl;
}

void Command::handleKickCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling KICK command" << std::endl;
}