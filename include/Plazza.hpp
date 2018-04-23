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

enum Information {
	PHONE_NUMBER,
	EMAIL_ADDRESS,
	IP_ADDRESS,
	UNDEFINED
};

namespace plazza {

class Plazza {
	public:
		explicit Plazza(int maxThreads);
		~Plazza();

		void sendCommandToSlaves(std::pair<std::string, Information>);

	private:
		std::vector<std::string> split(const std::string &, char) const noexcept;

		int _maxThreads;
		//std::vector<communication::Process> _slaves;
};

}
