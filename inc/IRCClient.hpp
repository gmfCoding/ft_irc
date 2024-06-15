#ifndef IRCCLIENT_H
# define IRCCLIENT_H
# include <iostream>
# include <unistd.h>
# include <netinet/in.h>
# include <unordered_set>
# include "CommandBuilder.hpp"
# include "AuthLevel.hpp"

class IRCServer;
class IRCChannel;
enum AuthStatus
{
    PASS,
    NICK,
    USER,
    AUTHENTICATED,
    AUTH_STATUS_COUNT
};


class IRCClient
{
private:
	int			fd;
	AuthLevel	authLevel;
	std::string	ipAddr;
	std::string nickname;
	std::string username;
	std::string realname;
	std::string buffer;
	IRCServer*	server;
	//IRCChannel*	currentChannel;
	std::unordered_set<IRCChannel*> channelsIn;
	bool Auth[AUTH_STATUS_COUNT];
public:
	IRCClient();
	IRCClient(int clientFd, IRCServer* server);
	~IRCClient();
	void			SetFd(int clientFd);
	int				GetFd() const;
	std::string&	GetNickname();
	std::string&	GetUsername();
	std::string		GetIpAddr();
	void			SetRealname(const std::string &realname);
	std::string&	GetRealname();
    void			SetIpAddr(const std::string &ipAddr);
	void			SetNickname(std::string &nickname);
	void			SetUsername(std::string &username);
	void			addData(const std::string &data);
	std::string 	GetData();
	void			SetData(const std::string& data);
	AuthLevel		GetAuthLevel() const;
	void			SetAuthLevel(AuthLevel level);
	void			clearData();
	IRCServer*		GetServer() const;
	std::string		GetHostname();
	bool			isInChannel(IRCChannel* channel) const;
	void			SetAuthStatus(AuthStatus status, bool received);
	bool			GetAuthStatus(AuthStatus status) const;
	void			authenticate();
	void			removeChannel(IRCChannel* channel);
	void			addChannel(IRCChannel* channel);
	std::unordered_set<IRCChannel*>	GetChannels() const;
};



#endif