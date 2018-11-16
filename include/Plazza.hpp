/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Main logic
*/

#pragma once

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <thread>
#include <netinet/in.h>

enum Information {
	PHONE_NUMBER,
	EMAIL_ADDRESS,
	IP_ADDRESS,
	UNDEFINED
};

struct command {
	std::string files;
	Information info;
};

std::ostream &operator<<(std::ostream &out, const command &cmd);
std::istream &operator>>(std::istream &in, command &cmd);

namespace communication {
	class Process;
}


#define PORT 51234

namespace plazza {

class Plazza {
	public:
		explicit Plazza(int maxThreads);
		~Plazza();

		int setupCommand(command);

	private:
		int sendCommandToSlave(command, communication::Process*, int);
		int recieveSlaveStatus(int, int, communication::Process*);

		bool doFilesExist(const std::vector<std::string>) const noexcept;
		void checkDeadSlaves() noexcept;
		void logCheck() const noexcept;
		std::vector<std::string> split(const std::string &, char) const noexcept;

		bool _master;
		bool _threadExit;

		std::thread _logCheckThread;

		int _maxThreads;
		int _masterSocket;
		std::vector<std::unique_ptr<communication::Process>> _slaves;
		struct sockaddr_in _server_addr;
};

}
