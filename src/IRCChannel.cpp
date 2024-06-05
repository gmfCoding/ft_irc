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
    return bannedClients.find(client) != bannedClients.end();
}

void IRCChannel::banClient(IRCClient* client)
{
    bannedClients.insert(client);
}

void IRCChannel::unbanClient(IRCClient* client)
{
    bannedClients.erase(client);
}

bool IRCChannel::hasKey() const
{
    //TODO: add key logic
    return (!key.empty());
}

const std::string& IRCChannel::GetKey() const { return key; }

bool IRCChannel::isFull() const
{
    //TODO: use a marco for the maxsize
    return (members.size() >= 10);
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

void IRCChannel::inviteClient(IRCClient* client)
{
    invited.insert(client);
}

/*
void                        IRCChannel::channelShutDown(){
        std::__1::vector<std::__1::string, std::__1::allocator<std::__1::string>> param;
			if (members.size() > 0){
				for(auto it = members.begin(); it != members.end(); it++){
					IRCClient* member = it->second;
					QuitCommand::handleQuitCommand(member, param);
				}
			}
			if (operators.size() > 0){
				for(auto it = operators.begin(); it != operators.end(); it++){
					IRCClient* op = it->second;
					QuitCommand::handleQuitCommand(op, param);
				}
			}
}
*/
