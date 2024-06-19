#include "CommandBuilder.hpp"

CommandBuilder::CommandBuilder(IRCServer* server) : server(server)
{
	if (availableCommands.empty())
	{
		initializeCommands();
		Command::commandMode = CommandMode();
	}
	return ;
}
CommandBuilder::~CommandBuilder() { return ; }

void	CommandBuilder::processCommand(IRCClient* client, const std::string& buffer)
{
	std::vector<std::string> tokens = tokenizeBuffer(buffer);
	if (tokens.empty())
		return ;
	std::string command = extractCommand(tokens);
	std::vector<std::string> parameters = extractParameters(tokens);
	if (command == "PRIVMSG")// add more if other commands they dont need leading colon/ or remove this and change it in the macro
		handleMultiWordParameters(parameters);
	AuthLevel authLevel = client->GetAuthLevel();
	routeCommand(client, command, parameters, authLevel);
}

/*
	combine paramteres back into 1 parameters from the leading colon:
*/
void	CommandBuilder::handleMultiWordParameters(std::vector<std::string>& parameters)
{
	if (!parameters.empty() && parameters[parameters.size() - 1][0] == ':')
	{ // remove leading colon
		std::string combinedMessage = parameters[parameters.size() - 1].substr(1);
		for (size_t i = parameters.size(); i > 0; --i)
		{
			if (parameters[i - 1][0] == ':')
			{
				for (size_t j = i; j < parameters.size(); ++j)
					combinedMessage += " " + parameters[j];
				parameters.resize(i);
				parameters[i - 1] = combinedMessage;
				break ;
			}
		}
	}
}

/*
    add other commands here
*/
void CommandBuilder::initializeCommands()
{
	availableCommands.push_back(Command("NICK", AuthPublic, Command::handleNickCommand));
	availableCommands.push_back(Command("USER", AuthPublic, Command::handleUserCommand));
	availableCommands.push_back(Command("PASS", AuthPublic, Command::handlePassCommand));
	availableCommands.push_back(Command("JOIN", AuthUser, Command::handleJoinCommand));
	availableCommands.push_back(Command("PRIVMSG", AuthUser, Command::handlePrivmsgCommand));
	availableCommands.push_back(Command("QUIT", AuthPublic, Command::handleQuitCommand));
	availableCommands.push_back(Command("MODE", AuthUser, Command::handleModeCommand));
	availableCommands.push_back(Command("TOPIC", AuthUser, Command::handleTopicCommand));
	availableCommands.push_back(Command("INVITE", AuthUser, Command::handleInviteCommand));
	availableCommands.push_back(Command("KICK", AuthUser, Command::handleKickCommand));
	availableCommands.push_back(Command("PART", AuthUser, Command::handlePartCommand));
}


std::vector<std::string> CommandBuilder::tokenizeBuffer(const std::string& buffer)
{
	std::vector<std::string> tokens;
	std::stringstream ss(buffer);
	std::string token;

	while (ss >> token)
	{
		if (token[0] == ':')
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
	return (tokens);
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
	if (client == NULL)
		return ;
	for (std::vector<Command>::const_iterator it = availableCommands.begin(); it != availableCommands.end(); ++it)
	{
		if (command == (*it).GetName() && authLevel >=(*it).GetAuthLevel())
		{
			(*it).execute(client, parameters);
			return ;
		}
	}
	client->GetServer()->clientSendData(client->GetFd(), ERR_UNKNOWNCOMMAND(client->GetNickname(), command));
}
