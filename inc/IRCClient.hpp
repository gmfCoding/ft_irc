#ifndef IRCCLIENT_H
# define IRCCLIENT_H
#include <iostream>
#include <unistd.h>

class Client
{

private:
	int			fd;
	std::string nickname;
	std::string username;
	std::string buffer;
public:
	Client(int fd);
	~Client();

	int				getFd();
	std::string&	getNickname();
	std::string&	getUsername();
	void			setNickname(std::string &nickname);
	void			setUsername(std::string &username);
	void			addData(std::string &data);
	std::string 	getData();
	void			clearData();
};



#endif