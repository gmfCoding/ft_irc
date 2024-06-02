#include "IRCChannel.hpp"

IRCChannel::IRCChannel() { return ; }
IRCChannel::IRCChannel(const std::string& channelName) : name(channelName) { return ; }
IRCChannel::~IRCChannel() { return ; }

const std::string&          IRCChannel::GetName() const { return name; }
void                        IRCChannel::addMember(IRCClient* client) { members.insert(client); }
void                        IRCChannel::addOperator(IRCClient* client) { operators.insert(client); }
void                        IRCChannel::removeOperator(IRCClient* client) { operators.erase(client); }
bool                        IRCChannel::isOperator(IRCClient* client) const { return operators.find(client) != operators.end(); }
bool                        IRCChannel::isMember(IRCClient* client) const { return members.find(client) != members.end(); }

void                        IRCChannel::removeMember(IRCClient* client)
{
    members.erase(client);
    operators.erase(client);
}

bool IRCChannel::isInviteOnly() const
{
    //TODO: add invite-only logic
    return (false);
}

bool IRCChannel::isBanned(IRCClient* client) const
{
    //TODO: add ban logic
    return (false);
}

bool IRCChannel::hasKey() const
{
    //TODO: add key logic
    return !key.empty();
}

const std::string& IRCChannel::GetKey() const { return key; }

bool IRCChannel::isFull() const
{
    //TODO: add channel full logic
    return (false);
}

bool IRCChannel::canSendMessage(IRCClient* client) const
{
    // TODO: add checks if the client can send msgs to this channel, for now return true assuming no restricion.
    return (true);
}

const std::string& IRCChannel::GetTopic() const
{
    return (topic);
}

std::string IRCChannel::GetMemberList() const
{
    std::string memberList;
    for (const auto& member : members)
    {
        memberList += member->GetNickname() + " ";
    }
    return memberList;
}


void IRCChannel::broadcast(const std::string& message)
{
    for (const auto& member : members)
    {
        member->GetServer()->clientSendData(member->GetFd(),message);
    }
}

bool IRCChannel::isInvited(IRCClient* client) const
{
    return invited.find(client) != invited.end();
}