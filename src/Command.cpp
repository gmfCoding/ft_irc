#include "Command.hpp"

Command::Command(){}

Command::Command(const std::string& name, AuthLevel level, std::function<void(IRCClient*, const std::vector<std::string>&)> func)
        : name(name), minAuthLevel(level), function(func) {}
Command::~Command() { return ; }

const std::string&  Command::GetName() const { return name; }
AuthLevel           Command::GetAuthLevel() const { return minAuthLevel; }
void				Command::execute(IRCClient* client, const std::vector<std::string>& params) const { function(client, params); }
