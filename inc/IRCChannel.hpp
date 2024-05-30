#ifndef IRCCHANNEL_HPP
# define IRCCHANNEL_HPP

# include <string>
# include <set>
# include <map>
# include "IRCClient.hpp"

class IRCChannel
{
private:
	std::string					name;
	std::set<IRCClient*>		members;
	std::set<IRCClient*>		operators;

public:
	IRCChannel(const std::string& channelName);
	~IRCChannel();
	const std::string&			GetName() const { return name; }
	const std::set<IRCClient*>& GetMembers() const { return members; }
	const std::set<IRCClient*>& GetOperators() const { return operators; }
	void						addMember(IRCClient* client);
	void						removeMember(IRCClient* client);
	void						addOperator(IRCClient* client);
	void						removeOperator(IRCClient* client);
	bool						isOperator(IRCClient* client) const;
	bool						isMember(IRCClient* client) const;

};

#endif