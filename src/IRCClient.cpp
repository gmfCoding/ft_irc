#include "IRCClient.hpp"

//IRCClient::IRCClient() : fd(-1) {}
IRCClient::IRCClient(int clientFd, IRCServer* server) : fd(clientFd), server(server), currentChannel(nullptr) {	this->authLevel = AuthPublic; return ; }

IRCClient::~IRCClient()
{
	std::cout << "destructor called on client" << std::endl;
	close(fd);
}

void			IRCClient::SetFd(int clientFd) { this->fd = clientFd; }
int				IRCClient::GetFd() const { return fd; }
std::string		IRCClient::GetData() { return buffer; }
void			IRCClient::addData(const std::string &data) { buffer += data; }
void			IRCClient::clearData() { buffer.clear(); }
std::string&	IRCClient::GetNickname() { return nickname; }
std::string&	IRCClient::GetUsername() { return username; }
void			IRCClient::SetNickname(std::string &nickname) { this->nickname = nickname; }
void			IRCClient::SetUsername(std::string &username) { this->username = username; }
void			IRCClient::SetIpAddr(const std::string &ipAddr) { this->ipAddr = ipAddr; }
std::string		IRCClient::GetIpAddr() { return ipAddr; }
AuthLevel		IRCClient::GetAuthLevel() const { return authLevel; }
void			IRCClient::SetAuthLevel(AuthLevel level) { authLevel = level; }
IRCServer*		IRCClient::GetServer() const { return server; }
void			IRCClient::SetCurrentChannel(IRCChannel* channel) { currentChannel = channel; }
IRCChannel*		IRCClient::GetCurrentChannel() const { return currentChannel; }


