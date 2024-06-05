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
# include <exception>
# include "IRCClient.hpp"
# include "CommandBuilder.hpp"
# include "IRCChannel.hpp"
# include "QuitCommand.hpp"

class IRCClient;
class IRCChannel;

enum	ErrorCode
{
	ERR_NO_ERROR,
	ERR_SETUP,
	ERR_POLL,
	ERR_FCNTL,
	ERR_SEND,
	ERR_NOSUCHCLIENTFD
};

class IRCServer : public QuitCommand
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

	int			serverFd;
	struct sockaddr_in			serverAddr;
	std::vector<struct pollfd>	pollFds;
	std::map<int, IRCClient*>	clients;
	std::map<std::string, IRCChannel*> channels;

public:
    IRCServer(int port, char *password);
    ~IRCServer();
    ErrorCode	Run();
	ErrorCode	err;
	void		erasePollFd(int clientFd);
	void		clientRemove(int clientFd);
	void		clientSendData(int clientFd, const std::string& data);
	//void		addChannel(const std::string& channelName);
	void		addChannel(IRCChannel* channel);
    IRCChannel*	GetChannel(const std::string& channelName);
	IRCClient*	GetClientByNickname(const std::string& nickname);
	char*		GetPassword();
	void 		serverShutdown();
	//exception msgs
	class ServerException : public std::exception{
			private:
				std::string _errMsg;
			public:
				ServerException(const std::string &msg) : _errMsg(msg){}
				virtual const char *what() const throw(){
					return _errMsg.c_str();
				};
		};
};

#endif