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
    std::unordered_set<IRCChannel*> channels = client->GetChannels();
    for(IRCChannel* channel : channels){
        channel->broadcast(msg, client->GetFd());
    }
    for(IRCChannel* channel : channels){
        channel->removeMember(client);
        if (channel->GetMemberList().empty())
            server->removeChannel(channel->GetName());
    }
    server->clientSendData(client->GetFd(), msg);
	client->GetServer()->clientRemove(client->GetFd());
}