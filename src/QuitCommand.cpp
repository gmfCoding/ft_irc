#include "QuitCommand.hpp"
#include "IRCRespondMacros.hpp"
#include "IRCServer.hpp"

QuitCommand::QuitCommand(){
}
QuitCommand::~QuitCommand(){
}

//Will need to check if the fd checking is correct for all situations
//as its just checking and fd above -1
int QuitCommand::handleQuitCommand(IRCClient* client, const std::vector<std::string>& parameters)
{//std::cout << "Handling QUIT command" << std::endl;
    //quit msg , nothing if no msg is inputed, else the users msg from paramater
    IRCServer *server = client->GetServer();
    client->GetServer()->clientSendData(client->GetFd(), RPL_QUIT(client->GetUsername(), parameters));
    //get the right poll to erase from the vector
    if (server){
        server->erasePollFd(client->GetFd());
        server->clientRemove(client->GetFd());
    }
    if (client->GetFd() > -1)
        close(client->GetFd());
}