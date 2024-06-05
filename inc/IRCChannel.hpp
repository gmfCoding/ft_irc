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

public:
	IRCChannel();
	IRCChannel(const std::string& channelName);
	~IRCChannel();
	const std::string&			GetName() const;
	void						addMember(IRCClient* client);
	void						removeMember(IRCClient* client);
	void						addOperator(IRCClient* client);
	void						removeOperator(IRCClient* client);
	bool						isOperator(IRCClient* client) const;
	bool						isMember(IRCClient* client) const;
	bool						isInviteOnly() const;
	bool						isBanned(IRCClient* client) const;
    void						banClient(IRCClient* client);
    void						unbanClient(IRCClient* client);
	bool						hasKey() const;
	const std::string&			GetKey() const;
	bool						isFull() const;
	const std::string&			GetTopic() const;
	std::string					GetMemberList() const;
	void						broadcast(const std::string& message);
	bool						isInvited(IRCClient* client) const;
	void						inviteClient(IRCClient* client);
	bool						canSendMessage(IRCClient* client) const;

};

#endif