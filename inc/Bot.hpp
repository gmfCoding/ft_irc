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
        void time();
        void help();
        void announce();
        void listMembers();
        void bombThreat();

};