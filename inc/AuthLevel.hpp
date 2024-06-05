#ifndef AUTHLEVEL_H
# define AUTHLEVEL_H


enum AuthLevel
{
    /// @brief For connect-ing clients, public information, might have potentially malicious actors. 
    AuthPublic,
    /// @brief For connected clients, secure for password protected servers.
    AuthUser,
    /// @brief For connected bots, slightly more privlidge than users.
    AuthBot,
    /// @brief For connected mods, privlidge to do channel managament.
    AuthAdmin
};

#endif