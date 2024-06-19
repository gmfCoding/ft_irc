#include "Command.hpp"

Command::Command(){}

//Command::Command(const std::string& name, AuthLevel level, std::function<void(IRCClient*, const std::vector<std::string>&)> func)
//				: name(name), minAuthLevel(level), function(func) {}

Command::Command(const std::string& name, AuthLevel level, void (*func)(IRCClient*, const std::vector<std::string>&))
				: name(name), minAuthLevel(level), function(func) {}
Command::~Command() { return ; }

const std::string&			Command::GetName() const { return name; }
AuthLevel					Command::GetAuthLevel() const { return minAuthLevel; }
void						Command::execute(IRCClient* client, const std::vector<std::string>& params) const { function(client, params); }
void						Command::handleModeCommand(IRCClient* client, const std::vector<std::string>& parameters) { commandMode.handleModeCommand(client, parameters); }

std::vector<std::string> Command::splitString(const std::string& str, char delimiter)
{
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delimiter))
		tokens.push_back(token);
	if (!str.empty() && str[str.size() - 1] == delimiter)
		tokens.push_back("");// capture empty bit
	return (tokens);
}
