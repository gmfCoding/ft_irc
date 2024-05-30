#ifndef IRCCLIENT_H
# define IRCCLIENT_H
# include <iostream>
# include <unistd.h>
# include <netinet/in.h>
# include "CommandBuilder.hpp"
# include "AuthLevel.hpp"

class IRCServer;

class IRCClient
{
private:
	int			fd;
	AuthLevel	authLevel;
	std::string	ipAddr;
	std::string nickname;
	std::string username;
	std::string buffer;
	IRCServer*	server;
public:
	IRCClient();
	IRCClient(int clientFd, IRCServer* server);
	~IRCClient();
	void			SetFd(int clientFd);
	int				GetFd() const;
	std::string&	GetNickname();
	std::string&	GetUsername();
	std::string		GetIpAddr();
    void			SetIpAddr(const std::string &ipAddr);
	void			SetNickname(std::string &nickname);
	void			SetUsername(std::string &username);
	void			addData(const std::string &data);
	std::string 	GetData();
	AuthLevel		GetAuthLevel() const;
	void			SetAuthLevel(AuthLevel level);
	void			clearData();
	IRCServer*		GetServer() const;

};



#endif