#ifndef IRCCLIENT_H
# define IRCCLIENT_H
#include <iostream>
#include <unistd.h>

class IRCClient
{
private:
	int			fd;
	std::string nickname;
	std::string username;
	std::string buffer;
public:
	IRCClient();
	IRCClient(int fd);
	~IRCClient();

	int				getFd();
	std::string&	getNickname();
	std::string&	getUsername();
	void			setNickname(std::string &nickname);
	void			setUsername(std::string &username);
	void			addData(const std::string &data);
	std::string 	getData();
	void			clearData();
};



#endif