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
# include <sstream>
# include <limits.h>
# include <string>
# include <cstring>
# include <fcntl.h>
# include <exception>
# include "IRCClient.hpp"
# include "CommandBuilder.hpp"
# include "IRCChannel.hpp"
# include "Command.hpp"

#ifndef HOST_NAME_MAX
# define HOST_NAME_MAX 255
#endif
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

typedef std::map<std::string, IRCChannel*>::iterator ChannelIterator;
typedef std::map<int, IRCClient*>::iterator ClientIterator;

class IRCServer
{
private:
	int									_port;
	char								*_password;
	ErrorCode							serverSetup();
	void								clientAccept();
	void								clientHandle(IRCClient* client);
	int									serverFd;
	struct sockaddr_in					serverAddr;
	std::vector<struct pollfd>			pollFds;
	std::map<int, IRCClient*>			clients;
	std::map<std::string, IRCChannel*>	channels;
public:
	IRCServer(int port, char *password);
	~IRCServer();
	ErrorCode							Run();
	ErrorCode							err;
	void								clientRemove(int clientFd);
	void								clientSendData(int clientFd, const std::string& data);
	void								removeChannel(const std::string& channelName);
	void								addChannel(IRCChannel* channel);
	IRCChannel*							GetChannel(const std::string& channelName);
	IRCClient*							GetClientByNickname(const std::string& nickname);
	char*								GetPassword();
	bool								isNicknameInUse(const std::string& nickname);
	void								erasePollFd(int clientFd);
	void 								serverShutdown();
	std::string 						GetPortName();
	std::string 						retriveHostName();
	std::map<int, IRCClient*> 			GetClients();
};


class ServerException : public std::exception {
    private:
    const char *m_message;

    public:
    ServerException(const char* message) : m_message(message) {}
    virtual const char* what() const throw() {
        return m_message;
    }
};
#endif