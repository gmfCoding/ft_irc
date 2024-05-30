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

//forward declare ircserver is there another way thats better?
class IRCServer;
class IRCClient;
/*
class CommandParameter
{
private:
    IRCServer* m_context;

public:
    CommandParameter(IRCServer* context) : m_context(context) {}
    ~CommandParameter() {}

    int         Count();
    std::string ReadString();
    int         ReadInt();
    //User        ReadUser();
};
*/
class Command;

static std::vector<Command>        availableCommands;
class CommandBuilder
{
private:
    IRCServer*                  server;
    std::vector<std::string>    tokenizeBuffer(const std::string& buffer);
    std::string                 extractCommand(const std::vector<std::string>& tokens);
    std::vector<std::string>    extractParameters(const std::vector<std::string>& tokens);
    static void                 initializeCommands();
    void                        routeCommand(IRCClient* client, const std::string& command, const std::vector<std::string>& parameters, AuthLevel authLevel);
public:
    CommandBuilder(IRCServer* server);
    ~CommandBuilder();
    void   processCommand(IRCClient* client, const std::string& buffer);
    

};

#endif