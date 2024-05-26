#include "IRCClient.hpp"

IRCClient::IRCClient() : fd(-1) {}
IRCClient::IRCClient(int fd) : fd(fd) { return ; }
IRCClient::~IRCClient() { close(fd); }

int				IRCClient::getFd() { return fd; }
std::string		IRCClient::getData() { return buffer; }
void			IRCClient::addData(const std::string &data) { buffer += data; }
void			IRCClient::clearData() { buffer.clear(); }

std::string&	IRCClient::getNickname() { return nickname; }
std::string&	IRCClient::getUsername() { return username; }
void			IRCClient::setNickname(std::string &nickname) { this->nickname = nickname; }
void			IRCClient::setUsername(std::string &username) { this->username = username; }
