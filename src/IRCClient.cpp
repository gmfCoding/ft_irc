#include "IRCClient.hpp"

IRCClient::IRCClient() : fd(-1) {}
IRCClient::IRCClient(int clientFd) : fd(clientFd) { return ; }
IRCClient::~IRCClient() 
{ 
	//close(fd); 
}

int				IRCClient::getFd() const { return fd; }
std::string		IRCClient::getData() { return buffer; }
void			IRCClient::addData(const std::string &data) { buffer += data; }
void			IRCClient::clearData() { buffer.clear(); }

std::string&	IRCClient::getNickname() { return nickname; }
std::string&	IRCClient::getUsername() { return username; }
void			IRCClient::setNickname(std::string &nickname) { this->nickname = nickname; }
void			IRCClient::setUsername(std::string &username) { this->username = username; }

void IRCClient::setFd(int clientFd) { this->fd = clientFd; }
void IRCClient::setIpAddr(const std::string &ipAddr) { this->ipAddr = ipAddr; }
std::string IRCClient::getIpAddr() { return ipAddr; }