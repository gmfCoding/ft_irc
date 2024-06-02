#include "IRCChannel.hpp"

IRCChannel::IRCChannel() { return ; }
IRCChannel::IRCChannel(const std::string& channelName) : name(channelName) { return ; }
IRCChannel::~IRCChannel() { return ; }

const std::string&          IRCChannel::GetName() const { return name; }
const std::set<IRCClient*>& IRCChannel::GetMembers() const { return members; }
const std::set<IRCClient*>& IRCChannel::GetOperators() const { return operators; }
void                        IRCChannel::addMember(IRCClient* client) { members.insert(client); }
void                        IRCChannel::removeOperator(IRCClient* client) { operators.erase(client); }
bool                        IRCChannel::isOperator(IRCClient* client) const { return operators.find(client) != operators.end(); }
bool                        IRCChannel::isMember(IRCClient* client) const { return members.find(client) != members.end(); }
void                        IRCChannel::removeMember(IRCClient* client)
{
    members.erase(client);
    operators.erase(client);
}

void                        IRCChannel::addOperator(IRCClient* client)
{
    if (members.find(client) != members.end())
    {
        operators.insert(client);
    }
}

void                        IRCChannel::channelShutDown(){
        std::__1::vector<std::__1::string, std::__1::allocator<std::__1::string>> param;
			if (members.size() > 0){
				for(auto it = members.begin(); it != members.end(); it++){
					IRCClient* member = it->second;
					QuitCommand::handleQuitCommand(member, param);
				}
			}
			if (operators.size() > 0){
				for(auto it = operators.begin(); it != operators.end(); it++){
					IRCClient* op = it->second;
					QuitCommand::handleQuitCommand(op, param);
				}
			}
}
