#pragma once
#include "Command.hpp"

class  QuitCommand : public Command{
    private:

    public:
        QuitCommand();
        ~QuitCommand();
        int handleQuitCommand(IRCClient* client, const std::vector<std::string>& parameters);
};