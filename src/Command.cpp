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
    std::cout << "Handling NICK command" << std::endl;
    std::string newNickname = parameters[0];
    client->SetNickname(newNickname);
}

void Command::handleUserCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling USER command" << std::endl;
    std::string username = parameters[0];
    client->SetUsername(username);
}

void Command::handlePassCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling PASS command" << std::endl;
    if (parameters.empty()) {
        std::cerr << "no password provided in PASS command" << std::endl;
        client->GetServer()->clientSendData(client->GetFd(), ERR_NEEDMOREPARAMS(client->GetNickname(), "Password"));
        return;
    }
    std::string password = parameters[0];
    if (password != (std::string)client->GetServer()->GetPassword())
    {
        std::cerr << "Error: Incorrect password provided" << std::endl;
        client->GetServer()->clientSendData(client->GetFd(), ERR_PASSWDMISMATCH(client->GetNickname()));
        return;
    }
    std::cout << "Authentication successful. Password verified." << std::endl;
    //could have different passwords for admin, that auto set you to the highest user
    client->SetAuthLevel(AuthLevel::AuthAdmin);
    client->GetServer()->clientSendData(client->GetFd(), RPL_WELCOME(client->GetNickname()));
      //maybe send welcome msg
    std::cout << "Password provided: " << password << std::endl;
}

void Command::handleJoinCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling JOIN command" << std::endl;
        if (parameters.empty())
    {
        // Send error message to client about missing channel name
        return;
    }

    std::string channelName = parameters[0];
    //IRCServer* server = client->getServer();
    //server->addChannel(channelName);
    //Channel* channel = server->getChannel(channelName);
    //if (channel)
    //{
    //    channel->addMember(client);
    //    // send confirmation to client about joining the channel
    //}
}

void Command::handlePartCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    if (parameters.empty())
    {
        // Send error message to client about missing channel name
        return;
    }

    //std::string channelName = parameters[0];
    //IRCServer* server = client->getServer();
    //Channel* channel = server->getChannel(channelName);
    //if (channel)
    //{
    //    channel->removeMember(client);
    //    // send confirmation to client about leaving the channel
    //}
}

void Command::handleKickCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling KICK command" << std::endl;
    if (parameters.size() < 2)
    {
        // Send error message to client about missing parameters
        return;
    }

    std::string channelName = parameters[0];
    std::string targetNick = parameters[1];
    //IRCServer* server = client->getServer();
    //Channel* channel = server->getChannel(channelName);
    //if (channel && channel->isOperator(client))
    //{
    //    IRCClient* targetClient = server->findClientByNickname(targetNick);
    //    if (targetClient)
    //    {
    //        channel->removeMember(targetClient);
    //        // send confirmation to client about kicking the target user
    //    }
    //}
}
void Command::handlePrivmsgCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling PRIVMSG command" << std::endl;
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
