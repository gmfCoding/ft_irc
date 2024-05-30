#ifndef IRCCHANNEL_HPP
# define IRCCHANNEL_HPP

# include <string>
# include <set>
# include <map>
# include "IRCClient.hpp"

class IRCClient;

class IRCChannel
{
private:
	std::string					name;
	std::set<IRCClient*>		members;
	std::set<IRCClient*>		operators;

public:
	IRCChannel();
	IRCChannel(const std::string& channelName);
	~IRCChannel();
	const std::string&			GetName() const;
	const std::set<IRCClient*>& GetMembers() const;
	const std::set<IRCClient*>& GetOperators() const;
	void						addMember(IRCClient* client);
	void						removeMember(IRCClient* client);
	void						addOperator(IRCClient* client);
	void						removeOperator(IRCClient* client);
	bool						isOperator(IRCClient* client) const;
	bool						isMember(IRCClient* client) const;

};

#endif