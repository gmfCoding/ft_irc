#include "IRCClient.hpp"
#include "Command.hpp"
//IRCClient::IRCClient() : fd(-1) {}
IRCClient::IRCClient(int clientFd, IRCServer* server, const std::string& host) : fd(clientFd), server(server), channelsIn(), hostname(host){	
	this->authLevel = AuthPublic; return ;
	std::fill(std::begin(Auth), std::end(Auth), false);
}

IRCClient::~IRCClient()
{
	 IRCServer *const server = this->GetServer();
	
	for (IRCChannel* channel : channelsIn)
	{
		channel->removeMember(this);
	}
	std::cout << "\033[1;33m" << "destructor called on client" << "\033[0m" << std::endl;
	if (this->GetFd() > -1)
		close(this->GetFd());
	else{
		server->err = ERR_NOSUCHCLIENTFD;
		return ;
	}
	server->err = ERR_NO_ERROR;
	clearData();
}

void			IRCClient::SetFd(int clientFd) { this->fd = clientFd; }
int				IRCClient::GetFd() const { return fd; }
std::string		IRCClient::GetData() { return buffer; }
void			IRCClient::addData(const std::string &data) { buffer += data; }
void			IRCClient::clearData() { buffer.clear(); }
void			IRCClient::SetData(const std::string& data) { buffer = data; }
std::string&	IRCClient::GetNickname() { return nickname; }
std::string&	IRCClient::GetUsername() { return username; }
void			IRCClient::SetNickname(std::string &nickname) { this->nickname = nickname; }
void			IRCClient::SetUsername(std::string &username) { this->username = username; }
void			IRCClient::SetRealname(const std::string &realname) { this->realname = realname; }
std::string&	IRCClient::GetRealname() { return (realname); }
void			IRCClient::SetIpAddr(const std::string &ipAddr) { this->ipAddr = ipAddr; }
std::string		IRCClient::GetIpAddr() { return ipAddr; }
AuthLevel		IRCClient::GetAuthLevel() const { return (authLevel); }
void			IRCClient::SetAuthLevel(AuthLevel level) { authLevel = level; }
IRCServer*		IRCClient::GetServer() const { return (server); }
bool			IRCClient::isInChannel(IRCChannel* channel) const { return (channelsIn.find(channel) != channelsIn.end()); }
void			IRCClient::removeChannel(IRCChannel* channel) { channelsIn.erase(channel); }
void			IRCClient::addChannel(IRCChannel* channel) { channelsIn.insert(channel); }
bool			IRCClient::GetAuthStatus(AuthStatus status) const { return Auth[status]; }
std::string		IRCClient::GetHost() { return this->hostname; }
std::unordered_set<IRCChannel*>	IRCClient::GetChannels() const { return channelsIn; }

std::string		IRCClient::GetHostname()
{
	std::string id;
	id = this->GetNickname() + "!" + this->GetUsername();
	return (id);
}

void			IRCClient::SetAuthStatus(AuthStatus status, bool received)
{
	Auth[status] = received;
	authenticate();
}

void IRCClient::authenticate()
{
	if (Auth[PASS] && Auth[NICK] && Auth[USER] && !Auth[AUTHENTICATED])
	{
		Auth[AUTHENTICATED] = true;
		SetAuthLevel(AuthUser);
		GetServer()->clientSendData(fd, RPL_WELCOME(nickname));
	}
}

//void			IRCClient::SetCurrentChannel(IRCChannel* channel) { currentChannel = channel; }
//IRCChannel*		IRCClient::GetCurrentChannel() const { return currentChannel; }
