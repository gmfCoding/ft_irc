#ifndef COMMAND_BUILDER_HPP
# define COMMAND_BUILDER_HPP
# include <vector>
# include <string>
# include <sstream>
# include <iostream>

# include "IRCServer.hpp"
# include "Command.hpp"
# include "IRCClient.hpp"
# include "AuthLevel.hpp"

class IRCServer;
class IRCClient;
class Command;

static std::vector<Command>		availableCommands;
class CommandBuilder
{
private:
	IRCServer*					server;
	std::vector<std::string>	tokenizeBuffer(const std::string& buffer);
	std::string					extractCommand(const std::vector<std::string>& tokens);
	std::vector<std::string>	extractParameters(const std::vector<std::string>& tokens);
	static void					initializeCommands();
	void						routeCommand(IRCClient* client, const std::string& command, const std::vector<std::string>& parameters, AuthLevel authLevel);
	void						handleMultiWordParameters(std::vector<std::string>& parameters);
public:
	CommandBuilder(IRCServer* server);
	~CommandBuilder();
	void						processCommand(IRCClient* client, const std::string& buffer);

};

#endif