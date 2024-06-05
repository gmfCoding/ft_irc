#ifndef IRCCHANNEL_HPP
# define IRCCHANNEL_HPP

# include <string>
# include <set>
# include <unordered_set>
# include "IRCClient.hpp"

class IRCClient;



class IRCChannel
{
private:
	std::string						name;
	std::string						key;
	std::string						topic;
	std::unordered_set<IRCClient*>	members;
	std::unordered_set<IRCClient*>	operators;
	std::unordered_set<IRCClient*>	invited;
	std::unordered_set<IRCClient*>	bannedClients;
	bool							inviteOnly;
	bool							topicRestricted;
	int								userLimit;

public:
	IRCChannel();
	IRCChannel(const std::string& channelName);
	~IRCChannel();
	void						broadcast(const std::string& message);
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
	bool						isInviteOnly() const;

//VVis not mandatoryVV
	bool						isBanned(IRCClient* client) const;
	bool						canSendMessage(IRCClient* client) const;
    void						banClient(IRCClient* client);
    void						unbanClient(IRCClient* client);
};

#endif