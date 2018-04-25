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
#include <netinet/in.h>

enum Information {
	PHONE_NUMBER,
	EMAIL_ADDRESS,
	IP_ADDRESS,
	UNDEFINED
};

typedef struct command_s {
	std::string files;
	Information info;
} command_t;

std::ostream &operator<<(std::ostream &out, const command_t &cmd);
std::istream &operator>>(std::istream &in, command_t &cmd);

namespace communication {
	class Process;
}


#define PORT 1337

namespace plazza {

class Plazza {
	public:
		explicit Plazza(int maxThreads);
		~Plazza();

		void setupCommand(command_t);

	private:
		int sendCommandToSlave(command_t, int, int);
		int recieveSlaveStatus(int, int);

		bool doFilesExist(const std::vector<std::string>) const noexcept;
		void checkDeadSlaves() noexcept;
		std::vector<std::string> split(const std::string &, char) const noexcept;

		int _maxThreads;
		int _masterSocket;
		std::vector<std::unique_ptr<communication::Process>> _slaves;
		struct sockaddr_in _server_addr;
};

}
