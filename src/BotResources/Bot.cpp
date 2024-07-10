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

Bot::Bot() : IRCClient(0, NULL, NULL){
	this->authLevel = AuthBot;
	for (int i = 0; i < AUTH_STATUS_COUNT; ++i)
		Auth[i] = false;
    std::string name = "Bot_Gear";
    SetRealname(name);
    SetUsername(name);
    SetNickname(name);
}

Bot* Bot::addbot(IRCChannel* chan, IRCServer* server, int fd){
	
	if (chan == nullptr){
		std::cerr << "Error: IRCChannel pointer is null in Bot::addbot" << std::endl;
        return nullptr;
	}
	Bot* bot = new Bot(fd, server, "host");
	if (bot == nullptr) {
        std::cerr << "Error: Failed to allocate memory for Bot in Bot::addbot" << std::endl;
        return nullptr;
    }
	chan->botTrue();
	return bot;
}
//need to make it so its the bot executing the commands, not the user, also
// need to check that the bot is in the channel to execute bot commands, a universal function for checking would work for all functs
// macos only atm
void Bot::bombThreat(IRCClient* client, const std::vector<std::string>& parameters){
	static_cast<void>(parameters);
    std::string name = client->GetNickname();
	std::set<IRCChannel*> channels = client->GetChannels();
	std::set<IRCChannel*>::iterator it = channels.begin();
	IRCChannel* channel = *it;
	client = channel->returnBot();
	if (client == nullptr){
        std::cerr << "Error, No Bot in Channel" << std::endl;
        return;
    }
	if(system("open bombThreat.mp4") == -1){
		std::cerr << "Error, No Video Found" << std::endl;
        return;
	}
	std::string msg = "Wake the fuck up samurai, we got a city to burn";
	std::vector<std::string> vec;
	
	vec.push_back(name);
	vec.push_back(msg);
	const std::vector<std::string>& test = vec;
	Command::handlePrivmsgCommand(client, test);
}

void Bot::time(IRCClient* client, const std::vector<std::string>& parameters){
	static_cast<void>(parameters);
    std::string name = client->GetNickname();
	std::set<IRCChannel*> channels = client->GetChannels();
	std::set<IRCChannel*>::iterator it = channels.begin();
	IRCChannel* channel = *it;
	if (!channel->hasBotBool()){
		std::cerr << "Error, No Bot in Channel" << std::endl;
        return;
	}
	client = channel->returnBot();
	std::time_t t = std::time(NULL);
    std::tm* local = std::localtime(&t);
    std::string msg = "Bot " + client->GetRealname() + ": Current local time (hrs,mins,secs): " + std::to_string(local->tm_hour) + ":" 
       + std::to_string(local->tm_min) + ":" + std::to_string(local->tm_sec);
    std::vector<std::string> vec;
	vec.push_back(name);
	vec.push_back(msg);
	const std::vector<std::string>& test = vec;
	Command::handlePrivmsgCommand(client, test);
}

void Bot::help(IRCClient* client, const std::vector<std::string>& parameters){
	static_cast<void>(parameters);
	std::string name = client->GetNickname();
	std::set<IRCChannel*> channels = client->GetChannels();
	std::set<IRCChannel*>::iterator it = channels.begin();
	IRCChannel* channel = *it;
	if (!channel->hasBotBool()){
		std::cerr << "Error, No Bot in Channel" << std::endl;
        return;
	}
	client = channel->returnBot();
	
	std::string msg = "List of available commands: LISTMEMBERS, TIME, ANNOUNCE, BOMBTHREAT";

	std::vector<std::string> vec;
	vec.push_back(name);
	vec.push_back(msg);
	const std::vector<std::string>& test = vec;
	Command::handlePrivmsgCommand(client, test);
}

void Bot::announce(IRCClient* client, const std::vector<std::string>& parameters) {
	static_cast<void>(parameters);
    std::string name = client->GetNickname();
	std::set<IRCChannel*> channels = client->GetChannels();
	std::set<IRCChannel*>::iterator it = channels.begin();
	IRCChannel* channel = *it;
	if (!channel->hasBotBool()){
		std::cerr << "Error, No Bot in Channel" << std::endl;
        return;
	}
	client = channel->returnBot();
    std::string msg = "Hello, I'm Bot_Gear, Type the prefix BOT_ followed by a command in caps, Use BOT_HELP for more.";

	std::vector<std::string> vec;
	vec.push_back(name);
	vec.push_back(msg);
	const std::vector<std::string>& test = vec;
	Command::handlePrivmsgCommand(client, test);
}

void Bot::listMembers(IRCClient* client, const std::vector<std::string>& parameters){
	static_cast<void>(parameters);
    std::set<IRCChannel*> channels = client->GetChannels();
	std::set<IRCChannel*>::iterator it = channels.begin();
	IRCChannel* channel = *it;
	if (!channel->hasBotBool()){
		std::cerr << "Error, No Bot in Channel" << std::endl;
        return;
	}
	std::set<IRCClient*> members = channel->GetMembers();
	std::string name = client->GetNickname();
	client = channel->returnBot();
	std::string msg;
	std::vector<std::string> vec;
   	msg = "The current members in this channel are: ";
    
	for (std::set<IRCClient*>::iterator it = members.begin(); it != members.end(); ++it){
		msg += "-" + (*it)->GetRealname() + ", ";
    }
	vec.push_back(name);
	vec.push_back(msg);
	const std::vector<std::string>& test = vec;
	Command::handlePrivmsgCommand(client, test);
}

Bot::~Bot(){}