#include <string>

class IRCServer
{
private:
    // probably make this a int or something
    char *port;

    char *password;

public:
    IRCServer(char *port, char *password);
    int Run();

    int Execute(User user, Command *command, CommandParameter params);
};

class User
{

};

class Client
{
    User user;
};

class CommandParameter
{
private:
    IRCServer& m_context;

public:
    CommandParameter(IRCServer& context) : m_context(context) {}
    ~CommandParameter() {}

    int         Count();
    std::string ReadString();
    int         ReadInt();
    User        ReadUser();
};  

class Command
{
    virtual int Run(User user, CommandParameter param) = 0;
};

class NickCommand : public Command
{
    int Run(User user, CommandParameter param);
};

int NickCommand::Run(User user, CommandParameter param)
{

}
