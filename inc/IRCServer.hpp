#ifndef IRCSERVER_H
# define IRCSERVER_H

# include <iostream>
# include <vector>
# include <map>
# include <algorithm>
# include <netinet/in.h>
# include <poll.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <cstring>
# include <fcntl.h>
# include "IRCClient.hpp"
# include "CommandBuilder.hpp"
//#include "Channel.hpp"

class IRCClient;

enum	ErrorCode
{
	ERR_NO_ERROR,
	ERR_SETUP,
	ERR_POLL,
	ERR_FCNTL,
	ERR_SEND
};

class IRCServer
{
private:
    // probably make this a int or something 
	//i made it int TODO:remove these comments
	int			_port;
	char		*_password;
	ErrorCode	serverSetup();
	//vvvvthesevvvv function even tho they are client based they reference a lot of server classes
	//and to handle errors correctly when it comes connections thought it was best to keep them here
	//or we can make stuff some stuff public
	void		clientAccept();
	void		clientHandle(IRCClient* client);
	void		clientRemove(int clientFd);

	int			serverFd;
	struct sockaddr_in			serverAddr;
	std::vector<struct pollfd>	pollFds;
	std::map<int, IRCClient*>	clients;

public:
    IRCServer(int port, char *password);
    ~IRCServer();
    ErrorCode	Run();
	ErrorCode	err;
	void		clientSendData(int clientFd, const std::string& data);
};

#endif