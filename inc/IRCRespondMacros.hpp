#ifndef IRCRESPONDMACROS_HPP
# define IRCRESPONDMACROS_HPP

//error Responses

#define ERR_NOSUCHNICK(source, nickname)                ": 401 " + source + " " + nickname + " :No such nick/channel" + "\r\n"
#define ERR_NOSUCHSERVER(source, server)                ": 402 " + source + " " + server + " :No such server" + "\r\n"
#define ERR_NOSUCHCHANNEL(source, channel)              ": 403 " + source + " " + channel + " :No such channel" + "\r\n"
#define ERR_CANNOTSENDTOCHAN(source, channel)           ": 404 " + source + " " + channel + " :Cannot send to channel" + "\r\n"
#define ERR_TOOMANYCHANNELS(source, channel)            ": 405 " + source + " " + channel + " :You have joined too many channels" + "\r\n"
#define ERR_WASNOSUCHNICK(source, nickname)             ": 406 " + source + " " + nickname + " :There was no such nickname" + "\r\n"
#define ERR_TOOMANYTARGETS(source)                      ": 407 " + source + " :Duplicate recipients. No message delivered" + "\r\n"
#define ERR_NOORIGIN(source)                            ": 409 " + source + " :No origin specified" + "\r\n"
#define ERR_NORECIPIENT(source, command)                ": 411 " + source + " :No recipient given (" + command + ")" + "\r\n"
#define ERR_NOTEXTTOSEND(source)                        ": 412 " + source + " :No text to send" + "\r\n"
#define ERR_NOTOPLEVEL(source, mask)                    ": 413 " + source + " " + mask + " :No toplevel domain specified" + "\r\n"
#define ERR_WILDTOPLEVEL(source, mask)                  ": 414 " + source + " " + mask + " :Wildcard in toplevel domain" + "\r\n"
#define ERR_UNKNOWNCOMMAND(source, command)             ": 421 " + source + " " + command + " :Unknown command" + "\r\n"
#define ERR_NOMOTD(source)                              ": 422 " + source + " :MOTD File is missing" + "\r\n"
#define ERR_NOADMININFO(source, server)                 ": 423 " + source + " " + server + " :No administrative info available" + "\r\n"
#define ERR_FILEERROR(source, fileop, file)             ": 424 " + source + " :File error doing " + fileop + " on " + file + "\r\n"
#define ERR_NONICKNAMEGIVEN(source)                     ": 431 " + source + " :No nickname given" + "\r\n"
#define ERR_ERRONEUSNICKNAME(source, nickname)          ": 432 " + source + " " + nickname + " :Erroneous nickname" + "\r\n"
#define ERR_NICKNAMEINUSE(source, nickname)             ": 433 " + source + " " + nickname + " :Nickname is already in use" + "\r\n"
#define ERR_NICKCOLLISION(source, nickname, user, host) ": 436 " + source + " " + nickname + " :Nickname collision KILL from " + user + "@" + host + "\r\n"
#define ERR_USERNOTINCHANNEL(source, nickname, channel) ": 441 " + source + " " + nickname + " " + channel + " :They aren't on that channel" + "\r\n"
#define ERR_NOTONCHANNEL(source, channel)               ": 442 " + source + " " + channel + " :You're not on that channel" + "\r\n"
#define ERR_USERONCHANNEL(source, nickname, channel)    ": 443 " + source + " " + nickname + " " + channel + " :is already on channel" + "\r\n"
#define ERR_NOLOGIN(source, user)                       ": 444 " + source + " " + user + " :User not logged in" + "\r\n"
#define ERR_SUMMONDISABLED(source)                      ": 445 " + source + " :SUMMON has been disabled" + "\r\n"
#define ERR_USERSDISABLED(source)                       ": 446 " + source + " :USERS has been disabled" + "\r\n"
#define ERR_NOTREGISTERED(source)                       ": 451 " + source + " :You have not registered" + "\r\n"
#define ERR_NEEDMOREPARAMS(source, command)             ": 461 " + source + " " + command + " :Not enough parameters" + "\r\n"
#define ERR_ALREADYREGISTERED(source)                   ": 462 " + source + " :You may not reregister" + "\r\n"
#define ERR_NOPERMFORHOST(source)                       ": 463 " + source + " :Your host isn't among the privileged" + "\r\n"
#define ERR_PASSWDMISMATCH(source)                      ": 464 " + source + " :Password incorrect" + "\r\n"
#define ERR_YOUREBANNEDCREEP(source)                    ": 465 " + source + " :You are banned from this server" + "\r\n"
#define ERR_KEYSET(source, channel)                     ": 467 " + source + " " + channel + " :Channel key already set" + "\r\n"
#define ERR_CHANNELISFULL(source, channel)              ": 471 " + source + " " + channel + " :Cannot join channel (+l)" + "\r\n"
#define ERR_UNKNOWNMODE(source, mode)                   ": 472 " + source + " " + mode + " :is unknown mode char to me" + "\r\n"
#define ERR_INVITEONLYCHAN(source, channel)             ": 473 " + source + " " + channel + " :Cannot join channel (+i)" + "\r\n"
#define ERR_BANNEDFROMCHAN(source, channel)             ": 474 " + source + " " + channel + " :Cannot join channel (+b)" + "\r\n"
#define ERR_BADCHANNELKEY(source, channel)              ": 475 " + source + " " + channel + " :Cannot join channel (+k)" + "\r\n"
#define ERR_NOPRIVILEGES(source)                        ": 481 " + source + " :Permission Denied- You're not an IRC operator" + "\r\n"
#define ERR_CHANOPRIVSNEEDED(source, channel)           ": 482 " + source + " " + channel + " :You're not channel operator" + "\r\n"
#define ERR_CANTKILLSERVER(source)                      ": 483 " + source + " :You can't kill a server!" + "\r\n"
#define ERR_NOOPERHOST(source)                          ": 491 " + source + " :No O-lines for your host" + "\r\n"
#define ERR_UMODEUNKNOWNFLAG(source)                    ": 501 " + source + " :Unknown MODE flag" + "\r\n"
#define ERR_USERSDONTMATCH(source)                      ": 502 " + source + " :Cannot change mode for other users" + "\r\n"

//numeric Responses

#define RPL_WELCOME(source)                             "001 " + source + " :Welcome " + source + " to the IRC network" + "\r\n"
#define RPL_YOURHOST(source, servername, version)       "002 " + source + " :Your host is " + servername + ", running version " + version + "\r\n"
#define RPL_CREATED(source, date)                       "003 " + source + " :This server was created " + date
#define RPL_MYINFO(source, servername, version, usermodes, chanmodes) "004 " + source + " " + servername + " " + version + " " + usermodes + " " + chanmodes + "\r\n"
#define RPL_BOUNCE(source, port, server)                "005 " + source + " :Try server " + server + ", port " + port + "\r\n"
#define RPL_USERHOST(source, userhost)                  ": 302 " + source + " :" + userhost + "\r\n"
#define RPL_ISON(source, nicknames)                     ": 303 " + source + " :" + nicknames + "\r\n"
#define RPL_AWAY(source, nickname, message)             ": 301 " + source + " " + nickname + " :" + message + "\r\n"
#define RPL_UNAWAY(source)                              ": 305 " + source + " :You are no longer marked as being away" + "\r\n"
#define RPL_NOWAWAY(source)                             ": 306 " + source + " :You have been marked as being away" + "\r\n"
#define RPL_WHOISUSER(source, nickname, username, hostname, realname) ": 311 " + source + " " + nickname + " " + username + " " + hostname + " * :" + realname + "\r\n"
#define RPL_WHOISSERVER(source, nickname, server, serverinfo) "312 " + source + " " + nickname + " " + server + " :" + serverinfo + "\r\n"
#define RPL_WHOISOPERATOR(source, nickname)             ": 313 " + source + " " + nickname + " :is an IRC operator" + "\r\n"
#define RPL_WHOISIDLE(source, nickname, idle, signon)   ": 317 " + source + " " + nickname + " " + idle + " " + signon + " :seconds idle, signon time" + "\r\n"
#define RPL_ENDOFWHOIS(source, nickname)                ": 318 " + source + " " + nickname + " :End of /WHOIS list" + "\r\n"
#define RPL_WHOISCHANNELS(source, nickname, channels)   ": 319 " + source + " " + nickname + " :" + channels + "\r\n"
#define RPL_WHOWASUSER(source, nickname, username, hostname, realname) ": 314 " + source + " " + nickname + " " + username + " " + hostname + " * :" + realname + "\r\n"
#define RPL_ENDOFWHOWAS(source, nickname)               ": 369 " + source + " " + nickname + " :End of WHOWAS" + "\r\n"
#define RPL_LISTSTART(source)                           ": 321 " + source + " Channel :Users  Name" + "\r\n"
#define RPL_LIST(source, channel, visible, topic)       ": 322 " + source + " " + channel + " " + visible + " :" + topic + "\r\n"
#define RPL_LISTEND(source)                             ": 323 " + source + " :End of /LIST" + "\r\n"
#define RPL_CHANNELMODEIS(source, channel, mode, modeparams) ": 324 " + source + " " + channel + " " + mode + " " + modeparams + "\r\n"
#define RPL_NOTOPIC(source, channel)                    ": 331 " + source + " " + channel + " :No topic is set" + "\r\n"
#define RPL_TOPIC(source, channel, topic)               ": 332 " + source + " " + channel + " :" + topic + "\r\n"
#define RPL_INVITING(source, channel, nickname)         ": 341 " + source + " " + channel + " " + nickname + "\r\n"
#define RPL_SUMMONING(source, user)                     ": 342 " + source + " " + user + " :Summoning user to IRC" + "\r\n"
#define RPL_VERSION(source, version, server, comments)  ": 351 " + source + " " + version + " " + server + " :" + comments + "\r\n"
#define RPL_WHOREPLY(source, channel, user, host, server, nick, status, hopcount, realname) ": 352 " + source + " " + channel + " " + user + " " + host + " " + server + " " + nick + " " + status + " :" + hopcount + " " + realname  + "\r\n"
#define RPL_ENDOFWHO(source, name)                      ": 315 " + source + " " + name + " :End of /WHO list" + "\r\n"
#define RPL_NAMREPLY(source, channel, users)            ": 353 " + source + " = " + channel + " :" + users + "\r\n"
#define RPL_ENDOFNAMES(source, channel)                 ": 366 " + source + " " + channel + " :End of /NAMES list." + "\r\n"
#define RPL_LINKS(source, mask, server, hopcount, serverinfo) ": 364 " + source + " " + mask + " " + server + " :" + hopcount + " " + serverinfo + "\r\n"
#define RPL_ENDOFLINKS(source, mask)                    ": 365 " + source + " " + mask + " :End of /LINKS list" + "\r\n"
#define RPL_BANLIST(source, channel, banid)             ": 367 " + source + " " + channel + " " + banid + "\r\n"
#define RPL_ENDOFBANLIST(source, channel)               ": 368 " + source + " " + channel + " :End of channel ban list" + "\r\n"
#define RPL_INFO(source, info)                          ": 371 " + source + " :" + info + "\r\n"
#define RPL_ENDOFINFO(source)                           ": 374 " + source + " :End of /INFO list" + "\r\n"
#define RPL_MOTDSTART(source)                           ": 375 " + source + " :- Message of the day - " + "\r\n"
#define RPL_MOTD(source, text)                          ": 372 " + source + " :- " + text + "\r\n"
#define RPL_ENDOFMOTD(source)                           ": 376 " + source + " :End of /MOTD command" + "\r\n"
#define RPL_YOUREOPER(source)                           ": 381 " + source + " :You are now an IRC operator" + "\r\n"
#define RPL_REHASHING(source, configfile)               ": 382 " + source + " " + configfile + " :Rehashing" + "\r\n"
#define RPL_TIME(source, server, time)                  ": 391 " + source + " " + server + " :" + time + "\r\n"
#define RPL_USERSSTART(source)                          ": 392 " + source + " :UserID   Terminal  Host" + "\r\n"
#define RPL_USERS(source, user, tty, host)              ": 393 " + source + " :" + user + " " + tty + " " + host + "\r\n"
#define RPL_ENDOFUSERS(source)                          ": 394 " + source + " :End of users" + "\r\n"
#define RPL_NOUSERS(source)                             ": 395 " + source + " :Nobody logged in" + "\r\n"
#define RPL_TRACELINK(source, version, destination, nextserver) ": 200 " + source + " Link " + version + " " + destination + " " + nextserver + "\r\n"
#define RPL_TRACECONNECTING(source, clas)              ": 201 " + source + " Try. " + clas + "\r\n"
#define RPL_TRACEHANDSHAKE(source, clas)               ": 202 " + source + " H.S. " + clas + "\r\n"
#define RPL_TRACEUNKNOWN(source, clas)                 ": 203 " + source + " ???? " + clas + "\r\n"
#define RPL_TRACEOPERATOR(source, clas)                ": 204 " + source + " Oper " + clas + "\r\n"
#define RPL_TRACEUSER(source, clas)                    ": 205 " + source + " User " + clas + "\r\n"
#define RPL_TRACESERVER(source, clas, server, hopcount, serverinfo) ": 206 " + source + " Serv " + clas + " " + server + " " + hopcount + " " + serverinfo + "\r\n"
#define RPL_TRACENEWTYPE(source, newtype)               ": 208 " + source + " NewType " + newtype + "\r\n"
#define RPL_TRACELOG(source, logfile)                   ": 261 " + source + " File " + logfile + "\r\n"
#define RPL_STATSLINKINFO(source, linkname, sendq, sentmsg, sentbytes, recvdmsg, recvdbytes, timeopen) ": 211 " + source + " " + linkname + " " + sendq + " " + sentmsg + " " + sentbytes + " " + recvdmsg + " " + recvdbytes + " " + timeopen + "\r\n"
#define RPL_STATSCOMMANDS(source, command)              ": 212 " + source + " " + command + "\r\n"
#define RPL_STATSCLINE(source, host, name, port, clas) ": 213 " + source + " C " + host + " * " + name + " " + port + " " + clas + "\r\n"
#define RPL_STATSNLINE(source, host, name, port, clas) ": 214 " + source + " N " + host + " * " + name + " " + port + " " + clas + "\r\n"
#define RPL_STATSILINE(source, host, port, clas)       ": 215 " + source + " I " + host + " * " + port + " " + clas + "\r\n"
#define RPL_STATSKLINE(source, host, port, clas)       ": 216 " + source + " K " + host + " * " + port + " " + clas + "\r\n"
#define RPL_STATSYLINE(source, clas, pingfreq)         ": 218 " + source + " Y " + clas + " " + pingfreq + "\r\n"
#define RPL_ENDOFSTATS(source, statsletter)             ": 219 " + source + " " + statsletter + " :End of /STATS report" + "\r\n"
#define RPL_STATSLLINE(source, host, sendq, sentmsg, sentbytes, recvdmsg, recvdbytes, timeopen) ": 241 " + source + " L " + host + " " + sendq + " " + sentmsg + " " + sentbytes + " " + recvdmsg + " " + recvdbytes + " " + timeopen + "\r\n"
#define RPL_STATSUPTIME(source, days, hours, minutes, seconds) ": 242 " + source + " :Server Up %d days %d:%02d:%02d", days, hours, minutes, seconds + "\r\n"
#define RPL_STATSOLINE(source, hostmask)                ": 243 " + source + " O " + hostmask + "\r\n"
#define RPL_STATSHLINE(source, hostmask)                ": 244 " + source + " H " + hostmask + "\r\n"
#define RPL_UMODEIS(source, usermode)                   ": 221 " + source + " " + usermode + "\r\n"
#define RPL_LUSERCLIENT(source, visible, invisible, servers) ": 251 " + source + " :There are " + visible + " users and " + invisible + " invisible on " + servers + " servers" + "\r\n"
#define RPL_LUSEROP(source, operators)                  ": 252 " + source + " " + operators + " :operator(s) online" + "\r\n"
#define RPL_LUSERUNKNOWN(source, unknown)               ": 253 " + source + " " + unknown + " :unknown connection(s)" + "\r\n"
#define RPL_LUSERCHANNELS(source, channels)             ": 254 " + source + " " + channels + " :channels formed" + "\r\n"
#define RPL_LUSERME(source, clients, servers)           ": 255 " + source + " :I have " + clients + " clients and " + servers + " servers" + "\r\n"
#define RPL_ADMINME(source, server)                     ": 256 " + source + " :Administrative info about " + server + "\r\n"
#define RPL_ADMINLOC1(source, location1)                ": 257 " + source + " :" + location1 + "\r\n"
#define RPL_ADMINLOC2(source, location2)                ": 258 " + source + " :" + location2 + "\r\n"
#define RPL_ADMINEMAIL(source, email)                   ": 259 " + source + " :" + email + "\r\n"
#define RPL_TRYAGAIN(source, command)                   ": 263 " + source + " " + command + " :Please wait a while and try again." + "\r\n"

//command Responses
#define RPL_JOIN(source, channel)                       ":" + source + " JOIN :" + channel + "\r\n"
#define RPL_PART(source, channel)                       ":" + source + " PART :" + channel + "\r\n"
#define RPL_PING(source, token)                         ":" + source + " PONG :" + token + "\r\n"
#define RPL_PRIVMSG(source, target, message)            ":" + source + " PRIVMSG " + target + " :" + message + "\r\n"
#define RPL_NOTICE(source, target, message)             ":" + source + " NOTICE " + target + " :" + message + "\r\n"
#define RPL_QUIT(source, message)                       ":" + source + " QUIT :Quit: " + message + "\r\n"
#define RPL_KICK(source, channel, target, reason)       ":" + source + " KICK " + channel + " " + target + " :" + reason + "\r\n"
#define RPL_MODE(source, channel, modes, args)          ":" + source + " MODE " + channel + " " + modes + " " + args + "\r\n"

#endif