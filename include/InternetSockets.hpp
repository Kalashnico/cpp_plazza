//
// Created by Nicolas Guerin on 17/04/2018.
//

#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include "Plazza.hpp"

namespace communication {
	class InternetSockets {
		public:
			explicit InternetSockets(int);
			~InternetSockets();

			command_t receive();

			int getSockeClient() const noexcept { return _socketClient; }

		private:
			int _portNumber;
			int _masterSocket;
			int _socketClient;
			char _message[BUFSIZ];
			struct sockaddr_in _server_addr;
	};
}
