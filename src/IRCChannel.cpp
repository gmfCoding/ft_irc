#include "IRCChannel.hpp"

IRCChannel::IRCChannel() { return ; }
IRCChannel::IRCChannel(const std::string& channelName) : name(channelName) { return ; }
IRCChannel::~IRCChannel() { return ; }

const std::string&          IRCChannel::GetName() const { return name; }
const std::set<IRCClient*>& IRCChannel::GetMembers() const { return members; }
const std::set<IRCClient*>& IRCChannel::GetOperators() const { return operators; }
void                        IRCChannel::addMember(IRCClient* client) { members.insert(client); }
void                        IRCChannel::removeOperator(IRCClient* client) { operators.erase(client); }
bool                        IRCChannel::isOperator(IRCClient* client) const { return operators.find(client) != operators.end(); }
bool                        IRCChannel::isMember(IRCClient* client) const { return members.find(client) != members.end(); }

void                        IRCChannel::removeMember(IRCClient* client)
{
    members.erase(client);
    operators.erase(client);
}

void                        IRCChannel::addOperator(IRCClient* client)
{
    if (members.find(client) != members.end())
    {
        operators.insert(client);
    }
}
