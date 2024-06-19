#include "Command.hpp"

void Command::handlePassCommand(IRCClient* client, const std::vector<std::string>& parameters)
{
	if (parameters.empty())
	{
		client->GetServer()->clientSendData(client->GetFd(), ERR_NEEDMOREPARAMS(client->GetNickname(), "Password"));
		return ;
	}
	std::string password = parameters[0];
	if (password != client->GetServer()->GetPassword())
	{
		client->GetServer()->clientSendData(client->GetFd(), ERR_PASSWDMISMATCH(client->GetNickname()));
		return ;
	}
	client->SetAuthStatus(PASS, true);
}