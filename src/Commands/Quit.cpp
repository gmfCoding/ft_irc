#include "Command.hpp"
#include "IRCServer.hpp"


void Command::handleQuitCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    IRCServer *server = client->GetServer();
	std::string msg = "Quiting the server";
	if (!parameters.empty())
		msg = parameters.at(0);
	std::string formated =  RPL_QUIT(client->GetNickname() + "!" + client->GetUsername() + "@" + client->GetHostName(), msg);
	std::map<int, IRCClient*> recievers = server->GetClients();
	for (const auto& recieverpair : recievers){
		IRCClient* reciever = recieverpair.second;
		if (reciever->GetFd() != client->GetFd()){
			server->clientSendData(reciever->GetFd(), formated);
		}
	}
    client->GetServer()->clientSendData(client->GetFd(), formated);
	client->GetServer()->clientRemove(client);
}