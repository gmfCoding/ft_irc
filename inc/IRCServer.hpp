#ifndef IRCSERVER_H
# define IRCSERVER_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
//#include <string>
#include <netinet/in.h>
#include <poll.h>
#include "IRCClient.hpp"
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <fcntl.h>
//#include "Channel.hpp"

enum	ErrorCode
{
	ERR_NO_ERROR,
	ERR_SETUP,
	ERR_POLL,
	ERR_FCNTL
};

class IRCServer
{
private:
    // probably make this a int or something 
	//i made it int TODO:remove these comments
	int			_port;
	char		*_password;
	ErrorCode	serverSetup();
	void		clientAccept();
	void		clientHandle(IRCClient &client);
	void		clientRemove(int clientFd);
	int			serverFd;
	struct sockaddr_in			serverAddr;
	std::vector<struct pollfd>	pollFds;
	std::map<int, IRCClient>	clients;

public:
    IRCServer(int port, char *password);
    ~IRCServer();
    ErrorCode	Run();
	ErrorCode	err;
};

#endif