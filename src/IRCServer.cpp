#include "IRCServer.hpp"


IRCServer::IRCServer(char *port, char *password) : port(port), password(password)
{

}

int IRCServer::Run()
{
	return (0);
}

AuthLevel NickCommand::GetAuthLevel()
{
    return (AuthPublic);
};

int NickCommand::Run(User user, CommandParameter param)
{
    std::string name = param.ReadString();
    int hopcount = param.ReadInt();
    return (0);
}
