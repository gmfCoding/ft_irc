#include "Command.hpp"

void Command::handlePassCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
    std::cout << "Handling PASS command" << std::endl;
    if (parameters.empty()) {
        std::cerr << "no password provided in PASS command" << std::endl;
        client->GetServer()->clientSendData(client->GetFd(), ERR_NEEDMOREPARAMS(client->GetNickname(), "Password"));
        return;
    }
    std::string password = parameters[0];
    if (password != (std::string)client->GetServer()->GetPassword())
    {
        std::cerr << "Error: Incorrect password provided" << std::endl;
        client->GetServer()->clientSendData(client->GetFd(), ERR_PASSWDMISMATCH(client->GetNickname()));
        return;
    }
    std::cout << "Authentication successful. Password verified." << std::endl;
    //could have different passwords for admin, that auto set you to the highest user
    client->SetAuthLevel(AuthLevel::AuthAdmin);
    client->GetServer()->clientSendData(client->GetFd(), RPL_WELCOME(client->GetNickname()));
      //maybe send welcome msg
    std::cout << "Password provided: " << password << std::endl;
}