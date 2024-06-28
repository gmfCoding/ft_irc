#include "Bot.hpp"

Bot::Bot(int clientFd, IRCServer* server, const std::string& host) : IRCClient(clientFd, server, host){	
	this->authLevel = AuthBot;
	for (int i = 0; i < AUTH_STATUS_COUNT; ++i)
		Auth[i] = false;
    std::string name = "Bot_Gear";
    SetRealname(name);
    SetUsername(name);
    SetNickname(name);
}

Bot::Bot() : IRCClient(NULL, NULL, NULL){
	this->authLevel = AuthBot;
	for (int i = 0; i < AUTH_STATUS_COUNT; ++i)
		Auth[i] = false;
    std::string name = "Bot_Gear";
    SetRealname(name);
    SetUsername(name);
    SetNickname(name);
}

Bot* Bot::addbot(IRCChannel* chan){
	Bot* bot = new Bot();
	std::vector<std::string> vec = {"Hello","Test"};
	const std::vector<std::string>& test = vec;
	bot->announce(bot, test);
	chan->botTrue();
	return bot;
}
//need to make it so its the bot executing the commands, not the user, also
// need to check that the bot is in the channel to execute bot commands, a universal function for checking would work for all functs
// macos only atm
void Bot::bombThreat(IRCClient* client, const std::vector<std::string>& parameters){
    system("open bombThreat.mp4");
    client->GetCurrentChannel()->broadcast("Wake the fuck up samurai, we got a city to burn");
}

void Bot::time(IRCClient* client, const std::vector<std::string>& parameters){
    std::time_t t = std::time(NULL);
    std::tm* local = std::localtime(&t);
    std::string msg = "Bot " + client->GetRealname() + ": Current local time (hrs,mins,secs): " + std::to_string(local->tm_hour) + ":" 
       + std::to_string(local->tm_min) + ":" + std::to_string(local->tm_sec);
    //output to users in channel, do we have a getchannel?
    client->GetCurrentChannel()->broadcast(msg);
}

void Bot::help(IRCClient* client, const std::vector<std::string>& parameters){
    std::string msg = "List of available commands:\n LISTMEMBERS\n TIME\n ANNOUNCE\n BOMBTHREAT";
    client->GetCurrentChannel()->broadcast(msg);
}

void Bot::announce(IRCClient* client, const std::vector<std::string>& parameters){
    std::string msg = "Hello, i'm bot: " + client->GetRealname() + 
    "\n Type the prefix BOT_ followed by a command in caps\n Use BOT_HELP for more.";
    client->GetCurrentChannel()->broadcast(msg);
    //anounce to current channel;
}

void Bot::listMembers(IRCClient* client, const std::vector<std::string>& parameters){
    std::set<IRCClient*> members = client->GetCurrentChannel()->GetMembers();
    
    //loop through members broadcasting them to the channel
    client->GetCurrentChannel()->broadcast("The current members in this channel are:\n");
    for (std::set<IRCClient*>::iterator it = members.begin(); it != members.end(); ++it){
        client->GetCurrentChannel()->broadcast("-" + (*it)->GetRealname() + "\n");
    }
}

// static int asciiValue(const std::string& str) {
//     int sum = 0;
    
//     for(char c : str)
//         sum += static_cast<int>(c);
//     return sum;
// }


// //terminal syntax will be BOT_CMD or /bot cmd
// int Bot::cmd(std::string& cmd){
//     int convert = asciiValue(cmd);
//     switch(convert){
//         case 1:
    
//             break;
//         case 2:

//             break;
//         case 3:
    
//             break;
//         case 4:

//             break;
//         case 5:

//             break;
//     }
// }

Bot::~Bot(){}