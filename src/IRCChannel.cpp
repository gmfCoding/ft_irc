#include "IRCChannel.hpp"

IRCChannel::IRCChannel() : userLimit(0), inviteOnly(false), topicRestricted(false) { return ; }
IRCChannel::IRCChannel(const std::string& channelName) : name(channelName), userLimit(0), inviteOnly(false), topicRestricted(false) { return ; }
IRCChannel::~IRCChannel() { delete this; return ; }

int							IRCChannel::GetUserLimit() { return (userLimit); }
const std::string&          IRCChannel::GetName() const { return (name); }
const std::string&			IRCChannel::GetTopic() const { return (topic); }
const std::string&			IRCChannel::GetKey() const { return (key); }
void                        IRCChannel::SetInviteOnly(bool set) { inviteOnly = set; }
void                        IRCChannel::SetTopicRestricted(bool set) { topicRestricted = set; }
void                        IRCChannel::SetKey(const std::string& newKey) { key = newKey; }
void                        IRCChannel::SetUserLimit(int limit) { userLimit = limit; }
void						IRCChannel::SetTopic(const std::string& newTopic) { topic = newTopic; }
void                        IRCChannel::addMember(IRCClient* client) { members.insert(client); client->addChannel(this); }
void                        IRCChannel::addOperator(IRCClient* client) { operators.insert(client); }
void                        IRCChannel::removeMember(IRCClient* client) { members.erase(client); operators.erase(client); client->removeChannel(this); }
void                        IRCChannel::removeOperator(IRCClient* client) { operators.erase(client); }
void						IRCChannel::removeUserLimit() { userLimit = 0; }
void                        IRCChannel::removeKey() { key.clear(); }
void						IRCChannel::inviteClient(IRCClient* client) { invited.insert(client); }
bool                        IRCChannel::hasKey() const { return (!key.empty()); }
bool                        IRCChannel::isTopicRestricted() const { return (topicRestricted); }
bool                        IRCChannel::isFull() const { return (members.size() >= userLimit); }
bool                        IRCChannel::isOperator(IRCClient* client) const { return (operators.find(client) != operators.end()); }
bool                        IRCChannel::isMember(IRCClient* client) const { return (members.find(client) != members.end()); }
bool						IRCChannel::isInviteOnly() const { return inviteOnly; }
bool						IRCChannel::isInvited(IRCClient* client) const { return (invited.find(client) != invited.end()); }

void IRCChannel::broadcast(const std::string& message)
{
	for (MemberIterator it = members.begin(); it != members.end(); ++it)
		(*it)->GetServer()->clientSendData((*it)->GetFd(), message);
}

void IRCChannel::broadcast(const std::string& message, int fd)
{
	for (MemberIterator it = members.begin(); it != members.end(); ++it)
		if ((*it)->GetFd() != fd)
			(*it)->GetServer()->clientSendData((*it)->GetFd(), message);
}

std::string IRCChannel::GetMemberList() const
{
    std::string memberList;
    for (MemberIterator it = members.begin(); it != members.end(); ++it)
	{
		if (isOperator(*it))
			memberList += "@" + (*it)->GetNickname() + " ";
		else
			memberList += (*it)->GetNickname() + " ";
	}
	if (!memberList.empty() && memberList.back() == ' ')
    	memberList.pop_back();
    return (memberList);
}

//only need these function if we add more functionality which is not aprt of subject
bool IRCChannel::isBanned(IRCClient* client) const { return bannedClients.find(client) != bannedClients.end(); }
void IRCChannel::banClient(IRCClient* client) { bannedClients.insert(client); }
void IRCChannel::unbanClient(IRCClient* client) { bannedClients.erase(client); }
bool IRCChannel::canSendMessage(IRCClient* client) const { return (true); }
