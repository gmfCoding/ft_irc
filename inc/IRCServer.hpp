#include <string>

enum AuthLevel
{
    /// @brief For connect-ing clients, public information, might have potentially malicious actors. 
    AuthPublic,
    /// @brief For connected clients, secure for password protected servers.
    AuthUser,
    /// @brief For connected bots, slightly more privlidge than users.
    AuthBot,
    /// @brief For connected mods, privlidge to do channel managament.
    AuthMod,
    /// @brief For connect admins, privlidge to shutdown / restart server.
    AuthAdmin
};

class User
{

};


class Client
{
    User user;
};

class IRCServer;

class CommandParameter
{
private:
    IRCServer* m_context;

public:
    CommandParameter(IRCServer* context) : m_context(context) {}
    ~CommandParameter() {}

    int         Count();
    std::string ReadString();
    int         ReadInt();
    User        ReadUser();
};

class Command
{
    virtual int Run(User user, CommandParameter param) = 0;
    virtual AuthLevel GetAuthLevel() = 0;
};

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



class NickCommand : public Command
{
public:
    int Run(User user, CommandParameter param);
    AuthLevel GetAuthLevel();
};

class CommandBuilder
{
    Command *Build(std::vector<std::string> tokens);
};