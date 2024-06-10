#include "CommandBuilder.hpp"

CommandBuilder::CommandBuilder(IRCServer* server) : server(server)
{
	if (availableCommands.empty())
		initializeCommands();
	return ;
}
CommandBuilder::~CommandBuilder() { return ; }

void CommandBuilder::processCommand(IRCClient* client, const std::string& buffer)
{
    std::vector<std::string> tokens = tokenizeBuffer(buffer);
    if (tokens.empty())
        return;

    std::string command = extractCommand(tokens);
    std::vector<std::string> parameters = extractParameters(tokens);
    AuthLevel authLevel = client->GetAuthLevel();
    routeCommand(client, command, parameters, authLevel);
}

/*
    add other commands here
*/
void CommandBuilder::initializeCommands()
{
	availableCommands.push_back(Command("NICK", AuthLevel::AuthPublic, Command::handleNickCommand));
	availableCommands.push_back(Command("USER", AuthLevel::AuthPublic, Command::handleUserCommand));
	availableCommands.push_back(Command("PASS", AuthLevel::AuthPublic, Command::handlePassCommand));
	availableCommands.push_back(Command("JOIN", AuthLevel::AuthUser, Command::handleJoinCommand));
	availableCommands.push_back(Command("PRIVMSG", AuthLevel::AuthUser, Command::handlePrivmsgCommand));
	availableCommands.push_back(Command("QUIT", AuthLevel::AuthPublic, Command::handleQuitCommand));
	availableCommands.push_back(Command("MODE", AuthLevel::AuthUser, Command::handleModeCommand));
	availableCommands.push_back(Command("TOPIC", AuthLevel::AuthUser, Command::handleTopicCommand));
	availableCommands.push_back(Command("INVITE", AuthLevel::AuthUser, Command::handleInviteCommand));
	availableCommands.push_back(Command("KICK", AuthLevel::AuthUser, Command::handleKickCommand));
	availableCommands.push_back(Command("PART", AuthLevel::AuthUser, Command::handlePartCommand));
}


std::vector<std::string> CommandBuilder::tokenizeBuffer(const std::string& buffer)
{
	std::vector<std::string> tokens;
	std::stringstream ss(buffer);
	std::string token;

	while (ss >> token)
	{
		if (token.front() == ':')
		{
			std::string rest;
			std::getline(ss, rest);
//			if (!rest.empty() && rest.front() == ' ')
//				rest = rest.substr(1);
			token += rest;
			tokens.push_back(token);
			break;
		}
		tokens.push_back(token);
    }
    return tokens;
}

/*
    gets the first token as the command
*/
std::string CommandBuilder::extractCommand(const std::vector<std::string>& tokens)
{
    return tokens.empty() ? "" : tokens[0];
}

/*
	gets the parameters
*/
std::vector<std::string> CommandBuilder::extractParameters(const std::vector<std::string>& tokens)
{
    return tokens.size() > 1 ? std::vector<std::string>(tokens.begin() + 1, tokens.end()) : std::vector<std::string>();
}

/*
	route the command based on authority level and command type
*/
void CommandBuilder::routeCommand(IRCClient* client, const std::string& command, const std::vector<std::string>& parameters, AuthLevel authLevel)
{
    std::cout << "Irc received command: " << command << std::endl;
    std::cout << "Irc parameters: ";
    for (const auto& param : parameters)
        std::cout << param << " "; 
    std::cout << std::endl;
    for (std::vector<Command>::const_iterator it = availableCommands.begin(); it != availableCommands.end(); ++it)
    {
        if (command == (*it).GetName() && authLevel >=(*it).GetAuthLevel())
        {
            (*it).execute(client, parameters);
            return;
        }
    }
    client->GetServer()->clientSendData(client->GetFd(), ERR_UNKNOWNCOMMAND(client->GetNickname(), command));
}
