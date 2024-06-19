#include "Command.hpp"
#include "IRCServer.hpp"


void Command::handleQuitCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    IRCServer *server = client->GetServer();
	std::string msg = "Quiting the server";
	if (!parameters.empty())
		msg = parameters.at(0);
	//std::string formated =  RPL_QUIT(client->GetNickname() + "!" + client->GetUsername() + "@" + client->GetHost(), msg);
	std::string formated = RPL_QUIT(client->GetHostname(), msg);
    // std::map<int, IRCClient*> recievers = server->GetClients();
	// for (const auto& recieverpair : recievers){
	// 	IRCClient* reciever = recieverpair.second;
	// 	if (reciever->GetFd() != client->GetFd()){
	// 		server->clientSendData(reciever->GetFd(), formated);
	// 	}
	// }
    // client->GetServer()->clientSendData(client->GetFd(), formated);
    std::set<IRCChannel*> channels = client->GetChannels();
    for (std::set<IRCChannel*>::iterator it = channels.begin(); it != channels.end(); ++it){
        (*it)->broadcast(formated, client->GetFd());
    }
    for (std::set<IRCChannel*>::iterator it = channels.begin(); it != channels.end(); ++it){
        (*it)->removeMember(client);
        if ((*it)->GetMemberList().empty())
            server->removeChannel((*it)->GetName());
    }
    server->clientSendData(client->GetFd(), formated);
	client->GetServer()->clientRemove(client->GetFd());
}