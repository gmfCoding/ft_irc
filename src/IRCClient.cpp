#include "IRCClient.hpp"

IRCClient::IRCClient() : fd(-1) {}
IRCClient::IRCClient(int clientFd) : fd(clientFd) { return ; }
IRCClient::~IRCClient(){close(fd);}

void			IRCClient::setFd(int clientFd) { this->fd = clientFd; }
int				IRCClient::getFd() const { return fd; }
std::string		IRCClient::getData() { return buffer; }
void			IRCClient::addData(const std::string &data) { buffer += data; }
void			IRCClient::clearData() { buffer.clear(); }
std::string&	IRCClient::getNickname() { return nickname; }
std::string&	IRCClient::getUsername() { return username; }
void			IRCClient::setNickname(std::string &nickname) { this->nickname = nickname; }
void			IRCClient::setUsername(std::string &username) { this->username = username; }
void			IRCClient::setIpAddr(const std::string &ipAddr) { this->ipAddr = ipAddr; }
std::string		IRCClient::getIpAddr() { return ipAddr; }

//TODO have to maybe make the other assignment operators too so i dont get errors
//aslo dont forget to add other variables we implement here
IRCClient& IRCClient::operator=(IRCClient&& other) noexcept {
    if (this != &other) {
        ipAddr = std::move(other.ipAddr);
        nickname = std::move(other.nickname);
        username = std::move(other.username);
        buffer = std::move(other.buffer);
        fd = other.fd;
        other.fd = -1; // invalidate the source object's fd
    }
    return *this;
}