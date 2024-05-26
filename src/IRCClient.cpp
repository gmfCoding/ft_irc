#include "IRCClient.hpp"

Client::Client(int fd) : fd(fd) { return ; }
Client::~Client() { close(fd); }

int				Client::getFd() { return fd; }
std::string		Client::getData() { return buffer; }
void			Client::addData(std::string &data) { buffer += data; }
void			Client::clearData() { buffer.clear(); }

std::string&	Client::getNickname() { return nickname; }
std::string&	Client::getUsername() { return username; }
void			Client::setNickname(std::string &nickname) { this->nickname = nickname; }
void			Client::setUsername(std::string &username) { this->username = username; }
