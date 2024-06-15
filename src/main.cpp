#include "IRCServer.hpp"
#include <stdlib.h>



void displayWelcomeMessage()
{
    std::string welcomeMessage = "\033[1;31m" // Set text color to red
    R"(
  _______   ______         _   _____       _____ 
 |  _____| |__  __|       | | |  __  \   /   _   \
 | |____      | |         | | | |_ / /  /  /   \__\
 |  ____|     | |         | | |  _  \  |  |     __
 | |          | |  ____   | | | | \  \  \  \ _ /  /
 |_|          |_| |____|  |_| |_|  \_ \  \_______/  by Chris,Kyle,Travis
                                     
    )" "\033[0m";
    std::cout << welcomeMessage << std::endl;
}

int main(int argc, char **argv)
{
    displayWelcomeMessage();
    if (argc != 3)
        return (1);

    int     port = atoi(argv[1]);
    char	*password = argv[2];
    IRCServer server = IRCServer(port, password);
    return server.Run();
}