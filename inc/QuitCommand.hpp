#pragma once
#include "Command.hpp"
#include "IRCRespondMacros.hpp"
#include "IRCServer.hpp"

class  QuitCommand : public Command{
    private:

    public:
        int handleQuitCommand(IRCClient* client, const std::vector<std::string>& parameters);
};