#include "IRCServer.hpp"


IRCServer::IRCServer(int port, char *password) : _port(port), _password(password)
{
	this->errorCode = serverSetup();
}

int IRCServer::Run()
{
	return (0);
}

int IRCServer::serverSetup()
{
	try
	{
		serverFd = socket(AF_INET, SOCK_STREAM, 0);
		int opt = 1;
		if (serverFd == -1)
			throw std::runtime_error("Failed to create socket");
		if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
			throw std::runtime_error("setsockopt failed");
		fcntl(serverFd, F_SETFL, O_NONBLOCK);
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_addr.s_addr = INADDR_ANY;
		serverAddr.sin_port = htons(_port);
		if (bind(serverFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
			throw std::runtime_error("Bind failed");
		if (listen(serverFd, SOMAXCONN) == -1)
			throw std::runtime_error("Listen failed");
		pollFds.push_back({serverFd, POLLIN, 0});
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}
	return (0);
}