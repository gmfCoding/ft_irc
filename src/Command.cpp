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

// TODO: check if the channel name is valid length <= 200)
void Command::handleJoinCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    if (parameters.empty())
    {
        client->GetServer()->clientSendData(client->GetFd(),ERR_NEEDMOREPARAMS(client->GetNickname(),"JOIN"));
        return ;
    }
    std::string channelName = parameters[0];
    std::string key = (parameters.size() > 1) ? parameters[1] : "";
    if (channelName.empty() || (channelName[0] != '&' && channelName[0] != '#'))
    {
        client->GetServer()->clientSendData(client->GetFd(), ERR_NOSUCHCHANNEL(client->GetNickname(), channelName));
        return;
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
        return;
    }
    if (channel->isBanned(client))
    {
        client->GetServer()->clientSendData(client->GetFd(), ERR_BANNEDFROMCHAN(client->GetNickname(), channelName));
        return;
    }
    if (channel->hasKey() && channel->GetKey() != key)
    {
        client->GetServer()->clientSendData(client->GetFd(), ERR_BADCHANNELKEY(client->GetNickname(), channelName));
        return;
    }
    if (channel->isFull())
    {
        client->GetServer()->clientSendData(client->GetFd(), ERR_CHANNELISFULL(client->GetNickname(), channelName));
        return;
    }
    channel->addMember(client);
    channel->broadcast(RPL_JOIN(client->GetNickname(), channelName));
    if (!channel->GetTopic().empty())
    {
        client->GetServer()->clientSendData(client->GetFd(), RPL_TOPIC(client->GetNickname(), channelName, channel->GetTopic()));
    }
    client->GetServer()->clientSendData(client->GetFd(), RPL_NAMREPLY(client->GetNickname(), channelName, channel->GetMemberList()));
    client->GetServer()->clientSendData(client->GetFd(), RPL_ENDOFNAMES(client->GetNickname(), channelName));
}

void Command::handlePartCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    if (parameters.empty())
    {
        // send error message to client about missing channel name
        return;
    }
}

void Command::handleKickCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling KICK command" << std::endl;
    if (parameters.size() < 2)
    {
        return;
    }
    std::string channelName = parameters[0];
    std::string targetNick = parameters[1];

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
