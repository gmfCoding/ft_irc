#ifndef IRCCLIENT_H
# define IRCCLIENT_H
#include <iostream>
#include <unistd.h>

class IRCClient
{
private:
	int			fd;
	std::string	ipAddr;
	std::string nickname;
	std::string username;
	std::string buffer;
public:
	IRCClient();
	IRCClient(int clientFd);
	~IRCClient();
	void			setFd(int clientFd);
	int				getFd() const;
	std::string&	getNickname();
	std::string&	getUsername();
	std::string		getIpAddr();
    void			setIpAddr(const std::string &ipAddr);
	void			setNickname(std::string &nickname);
	void			setUsername(std::string &username);
	void			addData(const std::string &data);
	std::string 	getData();
	void			clearData();
};



#endif