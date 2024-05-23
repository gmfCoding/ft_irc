

class IRCServer
{
private:
    // probably make this a int or something
    char *port;

    char *password;

public:
    IRCServer(char *port, char *password);
    int Run();
};