#include "IRCServer.hpp"


IRCServer::IRCServer(int port, char *password) : _port(port), _password(password)
{
	this->err = serverSetup();
}

IRCServer::~IRCServer()
{
	for (auto &client : clients)
		close(client.second.getFd());
	close(serverFd);
}

ErrorCode IRCServer::serverSetup()
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
		return (ERR_SETUP);
	}
	return (ERR_NO_ERROR);
}

/*
	this is where we are checking if any data has been sent to the server
	the poll is called to wait for events on the file descriptors 
	in the pollFds vector it will wait forever until the program is closed 
	or there is and error we loop over all the file descriptors and we check if
	there is data to read with this bad boy (revents & POLLIN) if there is data
	we accept the new client and add the client to map array of clients
*/
ErrorCode IRCServer::Run()
{
	if (this->err != ERR_NO_ERROR)
		return (this->err);
	while (true)
	{
		if((poll(pollFds.data(), pollFds.size(),-1) == -1))
			return (ERR_POLL);
		//int pollCount = poll(pollFds.data(), pollFds.size(), -1);
	//	if (pollCount == -1)
	//		return (ERR_POLL);
		for (size_t i = 0; i < pollFds.size(); ++i)
		{
			if (pollFds[i].revents & POLLIN)
			{
				if (pollFds[i].fd == serverFd)
				{
					clientAccept();
				}
				else
				{
					printf("we made it");
					clientHandle(clients[pollFds[i].fd]);
				}
			}
		}
	}
}

void	IRCServer::clientAccept()
{
	int clientFd = accept(serverFd, nullptr, nullptr);
	if (clientFd == -1)
		return ;
	if(fcntl(clientFd, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cerr << "Failed to set socket to non-blocking mode: " << strerror(errno) << std::endl;
		this->err = ERR_FCNTL;
		return ;
	}
	pollFds.push_back({clientFd, POLLIN, 0});
	clients[clientFd] = IRCClient(clientFd);
	std::cout << "Accepted client connection, FD: " << clientFd << std::endl;
}

void IRCServer::clientRemove(int clientFd)
{
	close(clientFd);
	pollFds.erase(std::remove_if(pollFds.begin(), pollFds.end(), [clientFd](pollfd &pfd)
	{
		return pfd.fd == clientFd;
	}), pollFds.end());
	clients.erase(clientFd);
}

void IRCServer::clientHandle(IRCClient &client)
{
	char buffer[512];
	int bytesRead = recv(client.getFd(), buffer, sizeof(buffer) - 1, 0);
	if (bytesRead <= 0)
	{
		clientRemove(client.getFd());
		return;
	}
	buffer[bytesRead] = '\0';
	client.addData(buffer);


	std::cout << "Received data from client " << client.getFd() << ": " << buffer << std::endl;
	// add some client magic here ;)

}

