#ifndef IRCCHANNEL_HPP
# define IRCCHANNEL_HPP

# include <string>
# include <set>
# include "IRCClient.hpp"
# include "Command.hpp"

class IRCClient;

typedef std::set<IRCClient*>::const_iterator MemberIterator;

class IRCChannel
{
private:
	std::string						name;
	std::string						key;
	std::string						topic;
	std::set<IRCClient*>			members;
	std::set<IRCClient*>			operators;
	std::set<IRCClient*>			invited;
	std::set<IRCClient*>			bannedClients;
	bool							inviteOnly;
	bool							topicRestricted;
	int								userLimit;

public:
	IRCChannel();
	IRCChannel(const std::string& channelName);
	~IRCChannel();
	void						broadcast(const std::string& message);
	void						broadcast(const std::string& message, int fd);
	int							GetUserLimit();
	const std::string&			GetName() const;
	const std::string&			GetKey() const;
	const std::string&			GetTopic() const;
	std::string					GetMemberList() const;
	void						SetUserLimit(int limit);
	void						SetTopic(const std::string& newTopic);
	void						SetTopicRestricted(bool set);
	void						SetInviteOnly(bool set);
	void						SetKey(const std::string& newKey);
	void						addMember(IRCClient* client);
	void						addOperator(IRCClient* client);
	void						removeUserLimit();
	void						removeMember(IRCClient* client);
	void						removeOperator(IRCClient* client);
	void						removeKey();
	bool						hasKey() const;
	void						inviteClient(IRCClient* client);
	bool						isFull() const;
	bool						isTopicRestricted() const;
	bool						isInvited(IRCClient* client) const;
	bool						isOperator(IRCClient* client) const;
	bool						isMember(IRCClient* client) const;
	void                        channelShutDown();
	bool						isInviteOnly() const;
	std::set<IRCClient*>		GetMembers() const;

//VVis not mandatoryVV
	bool						isBanned(IRCClient* client) const;
	bool						canSendMessage(IRCClient* client) const;
    void						banClient(IRCClient* client);
    void						unbanClient(IRCClient* client);
};

#endif