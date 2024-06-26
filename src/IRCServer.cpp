#include "IRCServer.hpp"
#include "GlobalVariables.hpp"

/*
	run the server setup
*/
IRCServer::IRCServer(int port, char *password) : _port(port), _password(password)
{
	this->err = serverSetup();
	if (err != 0)
		serverShutdown();
}

void		IRCServer::addChannel(IRCChannel* channel) { channels[channel->GetName()] = channel; }

/*
	on destruction loop through and close remaining cleint fd's
*/
IRCServer::~IRCServer()
{
	//for (ClientIterator kvp = clients.begin(); kvp != clients.end(); ++kvp)
	//{
	//	std::cout << "closed fd for " << kvp->first << std::endl;
	//	delete kvp->second;
	//}
	serverShutdown();
}

std::map<int, IRCClient*> IRCServer::GetClients(){ return (this->clients); }

std::string IRCServer::GetPortName()
{
	std::ostringstream oss;
	oss << this->_port;
	return (oss.str());
}

char*	IRCServer::GetPassword() { return(this->_password); }

/*
	here we create a socked/file desciptor i use a try catch
	to catch any errors thrown and i return the error code have not set up
	a good way to handle the error code yet but its something for now
	and at the moment no error handling done is done on the port number
	like 0 to 1023 are not meant to be used i believe

	//socket file descriptor
	socket(AF_INET for ip4, SOCK_STREAM is always used with TCP and both \\
	parties have connection until connection is terminated by wither party, protocol to be used with the socket)

	//socket options
	setsocketopt(socket_FD, SOL_SOCKET level- is for protocol independent options, \\
	SO_REUSEADDR allows for reuse ports quicker, a ptr value for the options, the size is used to say it is enabled);

	change file descriptor operations
	fcntl(socketFD, set the file statusflag, O_NONBLOCK make in and out operations of the socket return immediately )

	blind is used to set up the address and ports of the socket
	htons function takes a 16-bit number in host byte order and returns a 16-bit number in network byte order used in TCP/IP networks

	listen is used to set the socket passive SOMAXCONN set the max number allowed in
	and then i use push_back to add the server to the end of pollFds vector
*/
ErrorCode IRCServer::serverSetup()
{
	try
	{
		serverFd = socket(AF_INET, SOCK_STREAM, 0);
		int opt = 1;
		if (serverFd == -1)
			throw ServerException("Failed to create socket");
		if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
			throw ServerException("setsockopt failed");
		if(fcntl(serverFd, F_SETFL, O_NONBLOCK) == -1)
			throw ServerException("fcntl failed");
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_addr.s_addr = INADDR_ANY;
		serverAddr.sin_port = htons(_port);
		if (bind(serverFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
			throw ServerException("Bind failed");
		if (listen(serverFd, SOMAXCONN) == -1)
			throw ServerException("Listen failed");
		struct pollfd serverPollFd;
    	serverPollFd.fd = serverFd;
    	serverPollFd.events = POLLIN;
    	serverPollFd.revents = 0;
		pollFds.push_back(serverPollFd);
	}
	catch(const std::exception& e)
	{
		std::cerr << "SERVER SETUP ERR: " << e.what() << "\n Exit Code: " << ERR_SETUP << "\nExiting..." << std::endl;
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
	revent is returned event here is the struct for poll
		int    fd       The following descriptor being polled. 
		short  events   The input event flags . 
		short  revents  The output event flags .
*/

/*
ErrorCode IRCServer::Run()
{
	if (this->err != ERR_NO_ERROR)
		return (this->err);
	while (continueRunning && this->err == ERR_NO_ERROR)
	{
		//int pollCount = poll(pollFds.data(), pollFds.size(), 100);
		int pollCount = poll(pollFds.data(), pollFds.size(), -1);
		if (pollCount == -1)
			return (ERR_POLL);
		for (size_t i = 0; i < pollFds.size(); ++i)
		{
			if (pollFds[i].revents & POLLIN)
			{
				if (pollFds[i].fd == serverFd)
					clientAccept();
				else
					clientHandle(clients[pollFds[i].fd]);
			}
		}
	}
	return (ERR_NO_ERROR);
}
*/

ErrorCode IRCServer::Run()
{
	if (this->err != ERR_NO_ERROR)
		return (this->err);

	while (continueRunning && this->err == ERR_NO_ERROR)
	{
		int pollCount = poll(&pollFds[0], pollFds.size(), -1);
		if (pollCount == -1)
			return (ERR_POLL);
		std::vector<int> fdsToHandle;
		for (size_t i = 0; i < pollFds.size(); ++i)
			if (pollFds[i].revents & POLLIN)
				fdsToHandle.push_back(pollFds[i].fd);
		for (size_t i = 0; i < fdsToHandle.size(); ++i)
		{
			int fd = fdsToHandle[i];
			if (fd == serverFd)
				clientAccept();
			else
				if (clients.find(fd) != clients.end())
					clientHandle(clients[fd]);
		}
		std::vector<int> clientsToDelete;
		for (ClientIterator it = clients.begin(); it != clients.end(); ++it)
			if (it->second->isMarkedForDeletion())
				clientsToDelete.push_back(it->first);
		for (size_t i = 0; i < clientsToDelete.size(); ++i)
		{
			int fd = clientsToDelete[i];
			delete clients[fd];
			clients.erase(fd);
		}
	}
	return (ERR_NO_ERROR);
}

/*
	takes in clients and put them in the client map container which we can use later
	for and it allows fast retrieval of individual elements based on their keys,
	at the moment we just accept the client and dont pass in any client information
	but we can use those nullptr to pass in more information from the client
	we add the fd to the pollfds so we can check it for data in our loop

*/

std::string IRCServer::retriveHostName(){
	char host[HOST_NAME_MAX];
	if (gethostname(host, sizeof(host)) == 0)
		return std::string(host);
	else
		return "Unknown";
}

void	IRCServer::clientAccept()
{
	int clientFd = accept(serverFd, NULL, NULL);
	if (clientFd == -1)
		return ;
	if(fcntl(clientFd, F_SETFL, O_NONBLOCK) == -1)
	{
		this->err = ERR_FCNTL;
		return ;
	}
	struct pollfd clientPollFd;
    clientPollFd.fd = clientFd;
    clientPollFd.events = POLLIN;
    clientPollFd.revents = 0;
	std::string host = retriveHostName();
	//std::cout << "ASDASDASD  " << host << std::endl;
	pollFds.push_back((struct pollfd){clientFd, POLLIN, 0});
	clients[clientFd] = new IRCClient(clientFd, this, host);
	std::cout << "\033[1;32m" << "accepted client connection, FD: " << "\033[0m" << clientFd << std::endl;
}

/*
	removes client and closed fd's, and removes from the pollfds
	remove_if Remove elements from range
*/
void IRCServer::erasePollFd(int clientFd)
{

	for (std::vector<pollfd>::iterator it = pollFds.begin(); it != pollFds.end(); ++it)
	{
		if (it->fd == clientFd)
		{
			pollFds.erase(it);
			break ;
		}
	}
}

void IRCServer::clientRemove(int clientfd)
{
	ClientIterator it = clients.find(clientfd);
	if (it != clients.end())
	{
		IRCClient* client = it->second;
		std::set<IRCChannel*> channels = client->GetChannels();
		for (std::set<IRCChannel*>::iterator chanIt = channels.begin(); chanIt != channels.end(); ++chanIt)
		{
			IRCChannel* channel = *chanIt;
			channel->removeMember(client);
			if (channel->GetMemberList().empty())
				removeChannel(channel->GetName());
		}
		client->markForDeletion();
		erasePollFd(clientfd);
	}
}

/*
	here is here we read the data
	recv is used to retrieve data from a connection
	recv(file descriptor of client, a place to store the data, the max sife of the data length, optional flag)
*/
void IRCServer::clientHandle(IRCClient* client)
{
	char buffer[512];
	int bytesRead = recv(client->GetFd(), buffer, sizeof(buffer) - 1, 0);
	if (bytesRead <= 0)
	{
		clientRemove(client->GetFd());
		return ;
	}
	buffer[bytesRead] = '\0';
	client->addData(buffer);
	std::cout << "\033[1;32m" << "Client FD: " << "\033[0m" << client->GetFd() << ".." << std::endl;
	std::cout << buffer << std::endl;
	std::string commandBuffer = client->GetData();
	size_t pos;
	while ((pos = commandBuffer.find_first_of("\r\n")) != std::string::npos)
	{
		size_t end = commandBuffer.find("\r\n");
		if (end == std::string::npos)
			end = commandBuffer.find("\n");
		if (end != std::string::npos)
		{
			std::string rawCommand = commandBuffer.substr(0, end);
			if (commandBuffer[end] == '\r' && commandBuffer[end + 1] == '\n')
			    commandBuffer.erase(0, end + 2); // "\r\n"
			else
			    commandBuffer.erase(0, end + 1); // "\n"
			CommandBuilder commandBuilder(this);
			commandBuilder.processCommand(client, rawCommand);
		}
		else
			break ;
	}
	client->SetData(commandBuffer);
}

/*
	the send fucntion  take in the clients socket fd and can only be used it the socket is
	connected
	sockets operate at the byte level and can only transmit raw bytes so we may have to converting data to binary format
	for bonus here
*/
void	IRCServer::clientSendData(int clientFd, const std::string& data)
{
	//std::string formattedData = data + "\r\n"; // IRC messages end with CRLF//already sending with macros
	ssize_t bytesSent = send(clientFd, data.c_str(), data.size(), 0);
	if (bytesSent == -1)
	{
		this->err = ERR_SEND;
		std::cout << "failed to send data to client" << std::endl;
		// TODO: handle errors properly maybe remove client
		//clientRemove(clientFd);
	}
}

IRCChannel* IRCServer::GetChannel(const std::string& channelName)
{
	ChannelIterator kvp = channels.find(channelName);
	if (kvp != channels.end())
		return (kvp->second);
	return (NULL);
}

void IRCServer::serverShutdown()
{
	if (this->clients.size() > 0) {
		for (ClientIterator it = clients.begin(); it != clients.end(); ++it) {
			IRCClient* client = it->second;
			clientRemove(client->GetFd());
			delete client;
		}
	}
	if (this->channels.size() > 0) {
		for (ChannelIterator it = channels.begin(); it != channels.end(); ++it) {
			IRCChannel* chris_chan = it->second;
			chris_chan->channelShutDown();
			delete chris_chan;
		}
	}
	channels.clear();
	if (serverFd)
		close(serverFd);
	std::cout  << "\033[1;32m" << "☺ Server has been shut down gracefully ☻" << "\033[0m" << std::endl;
}
//we could have the client in a map with a string instead of a int(fdsockect) so we dont need to loop through clients

IRCClient* IRCServer::GetClientByNickname(const std::string& nickname)
{
	for (ClientIterator kvp = clients.begin(); kvp != clients.end(); ++kvp)
		if (kvp->second->GetNickname() == nickname)
			return (kvp->second);
	return (NULL);
}

bool	IRCServer::isNicknameInUse(const std::string& nickname)
{
	for (ClientIterator kvp = clients.begin(); kvp != clients.end(); ++kvp)
		if (kvp->second->GetNickname() == nickname)
			return (true);
	return (false);
}

void IRCServer::removeChannel(const std::string& channelName)
{
	ChannelIterator kvp = channels.find(channelName);
	if (kvp != channels.end())
	{
		delete kvp->second;
		channels.erase(kvp);
	}
}
