#pragma once
#include <ctime>
#include <sstream>
#include <string>
#include <iostream>
#include "IRCClient.hpp"

class Bot : public IRCClient{
    private:

    public:
        Bot(int clientFd, IRCServer* server, const std::string& host);
        ~Bot();

        int cmd(std::string& cmd);
        static void time(IRCClient* client, const std::vector<std::string>& parameters);
        static void help(IRCClient* client, const std::vector<std::string>& parameters);
        static void announce(IRCClient* client, const std::vector<std::string>& parameters);
        static void listMembers(IRCClient* client, const std::vector<std::string>& parameters);
        static void bombThreat(IRCClient* client, const std::vector<std::string>& parameters);

};