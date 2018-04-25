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


namespace plazza {

class Plazza {
	public:
		explicit Plazza(int maxThreads);
		~Plazza();

		void sendCommandToSlaves(command_t);

	private:
		bool doFilesExist(const std::vector<std::string>) const noexcept;
		int calculateNewSlaves(int) const noexcept;
		std::vector<std::string> split(const std::string &, char) const noexcept;

		int _maxThreads;
		int _masterSocket;
		std::vector<std::unique_ptr<communication::Process>> _slaves;
};

}
