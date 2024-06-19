#include <stdlib.h>
#include <csignal>
#include "GlobalVariables.hpp"
#include "IRCServer.hpp"

bool continueRunning = true;

void displayWelcomeMessage()
{
    std::string colorStart = "\033[1;31m"; // Set text color to red
    std::string welcomeMessage = 
    "  _______   ______         _   _____       _____ \n"
    " |  _____| |__  __|       | | |  __  \\   /   _   \\\n"
    " | |____      | |         | | | |_ / /  /  /   \\__\\\n"
    " |  ____|     | |         | | |  _  \\  |  |     __\n"
    " | |          | |  ____   | | | | \\  \\  \\  \\ _ /  /\n"
    " |_|          |_| |____|  |_| |_|  \\_ \\  \\_______/  by Chris,Kyle,Travis\n"
    "                                     \n";
    std::string colorEnd = "\033[0m"; // Reset text color
    std::cout << colorStart << welcomeMessage << colorEnd << std::endl;
}

void handleCtrlC(int sig)
{
	continueRunning = false;
}

int main(int argc, char **argv)
{
    displayWelcomeMessage();
    if (argc != 3)
        return (1);
    signal(SIGINT, handleCtrlC);

    int     port = atoi(argv[1]);
    char	*password = argv[2];
    IRCServer server = IRCServer(port, password);
    return server.Run();
}