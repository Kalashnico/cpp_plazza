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

namespace communication {
	class Process;
}

namespace plazza {

class Plazza {
	public:
		explicit Plazza(int maxThreads);
		~Plazza();

		void sendCommandToSlaves(std::pair<std::string, Information>);

	private:
		bool doFilesExist(const std::vector<std::string>) const noexcept;
		int calculateNewSlaves(int) const noexcept;
		std::vector<std::string> split(const std::string &, char) const noexcept;

		int _maxThreads;
		std::vector<std::unique_ptr<communication::Process>> _slaves;
};

}
