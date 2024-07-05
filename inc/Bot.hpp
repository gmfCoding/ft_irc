#ifndef BOT_HPP
# define BOT_HPP
# include <ctime>
# include <sstream>
# include <string>
# include <iostream>
# include "IRCClient.hpp"

class IRCServer;
class IRCClient;
class IRCChannel;

class Bot : public IRCClient{
    private:

    public:
        Bot(int clientFd, IRCServer* server, const std::string& host);
		Bot();
        ~Bot();

		static Bot* addbot(IRCChannel* chan, IRCServer* server, int fd);
        int 		cmd(std::string& cmd);
        static void time(IRCClient* client, const std::vector<std::string>& parameters);
        static void help(IRCClient* client, const std::vector<std::string>& parameters);
        static void announce(IRCClient* client, const std::vector<std::string>& parameters);
        static void listMembers(IRCClient* client, const std::vector<std::string>& parameters);
        static void bombThreat(IRCClient* client, const std::vector<std::string>& parameters);

};

#endif