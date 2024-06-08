#include "Command.hpp"
#include "IRCServer.hpp"


void Command::handleQuitCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    IRCServer *server = client->GetServer();
    //default quit, no parameters
    if (parameters.empty())
        client->GetServer()->clientSendData(client->GetFd(), RPL_QUIT(client->GetNickname(), "Quiting the server"));
    else{
        const std::string& first = parameters.at(0);
        const char *msg = first.c_str();
        client->GetServer()->clientSendData(client->GetFd(), RPL_QUIT(client->GetUsername(), msg));
    }
    //polls, ports, sockets, memory, fds
	client->GetServer()->clientRemove(client);
}