#include "IRCServer.hpp"
//kyle is here
int main(int argc, char **argv)
{

    if (argc != 3)
        return (1);

    char    *port = argv[1];
    char    *password = argv[2];

    IRCServer server = IRCServer(port, password);
    return server.Run();
}