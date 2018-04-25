//
// Created by Nicolas Guerin on 17/04/2018.
//

#include <iostream>
#include <zconf.h>
#include <ctime>
#include <sstream>
#include <cstring>
#include "InternetSockets.hpp"
#include "Exceptions.hpp"

namespace communication {
	InternetSockets::InternetSockets(int masterSocket) : _portNumber{1337}, _masterSocket{masterSocket}
	{
		_socketClient = socket(AF_INET , SOCK_STREAM , 0);

		_server_addr.sin_family = AF_INET;
		_server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		_server_addr.sin_port = htons(_portNumber);

		if (connect(_socketClient, (struct sockaddr *)&_server_addr, sizeof(_server_addr)) < 0)
			throw exceptions::ConnectError("Failed to connect to master");
	}

	InternetSockets::~InternetSockets()
	{
		close(_socketClient);
	}

	void InternetSockets::sendToMaster(int nb) const
	{
		switch (nb) {
			case -1:
				if (send(_masterSocket, "-1", 2, 0) < 0)
					throw exceptions::SendError("Failed to send response to master");
				break;
			case 1:
				if(send(_masterSocket, "1", 1, 0) < 0)
					throw exceptions::SendError("Failed to send response to master");
				break;
			default:
				if(send(_masterSocket, "0", 1, 0) < 0)
					throw exceptions::SendError("Failed to send response to master");
				break;
		}
	}

	command_t InternetSockets::receive()
	{
		ssize_t readSize{};

		std::memset(_message, 0, BUFSIZ);
		readSize = recv(_socketClient, _message, BUFSIZ, 0);

		if (readSize < 0)
			throw exceptions::RecieveError("Failed to recieve command");

		std::istringstream iss(_message);
		command_t cmd{"", UNDEFINED};

		iss >> cmd;
		return  cmd;
	}
}
