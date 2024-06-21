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
// macos only atm
void Bot::bombThreat(){
    system("open bombThreat.mp4");
    this->GetCurrentChannel()->broadcast("Wake the fuck up samurai, we got a city to burn\n");
}

void Bot::time(){
    std::time_t t = std::time(NULL);
    std::tm* local = std::localtime(&t);
    std::string msg = "Bot " + this->GetRealname() + ": Current local time (hrs,mins,secs): " + std::to_string(local->tm_hour) + ":" 
       + std::to_string(local->tm_min) + ":" + std::to_string(local->tm_sec);
    //output to users in channel, do we have a getchannel?
    this->GetCurrentChannel()->broadcast(msg);
}

void Bot::help(){
    std::string msg = "List of available commands:\n LISTMEMBERS\n TIME\n ANNOUNCE\n BOMBTHREAT";
    this->GetCurrentChannel()->broadcast(msg);
}

void Bot::announce(){
    std::string msg = "Hello, i'm bot: " + this->GetRealname() + 
    "\n Type the prefix BOT_ followed by a command in caps\n Use BOT_HELP for more.";
    this->GetCurrentChannel()->broadcast(msg);
    //anounce to current channel;
}

void Bot::listMembers(){
    std::set<IRCClient*> members = this->GetCurrentChannel()->GetMembers();
    
    //loop through members broadcasting them to the channel
    this->GetCurrentChannel()->broadcast("The current members in this channel are:\n");
    for (std::set<IRCClient*>::iterator it = members.begin(); it != members.end(); ++it){
        this->GetCurrentChannel()->broadcast("-" + (*it)->GetRealname() + "\n");
    }
}

static int asciiValue(const std::string& str) {
    int sum = 0;
    
    for(char c : str)
        sum += static_cast<int>(c);
    return sum;
}


//terminal syntax will be BOT_CMD or /bot cmd
int Bot::cmd(std::string& cmd){
    int convert = asciiValue(cmd);
    switch(convert){
        case 1:
    
            break;
        case 2:

            break;
        case 3:
    
            break;
        case 4:

            break;
        case 5:

            break;
    }
}

Bot::~Bot(){}