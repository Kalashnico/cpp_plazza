/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Main logic
*/

#include <iostream>
#include <sstream>
#include <unistd.h>
#include "Plazza.hpp"
#include "Process.hpp"

namespace plazza {

Plazza::Plazza(int maxThreads)
	: _maxThreads(maxThreads)
{}

Plazza::~Plazza()
{}

void Plazza::sendCommandToSlaves(std::pair<std::string, Information> command)
{
	auto files = split(command.first, ' ');
	auto nbrFiles = files.size();
	auto slavesToCreate = calculateNewSlaves(nbrFiles);

	for (int i = 0; i < slavesToCreate; i++)
		_slaves.emplace_back(std::make_unique<communication::Process>(_maxThreads));

	int iterator = 0;

	for (const auto &slave : _slaves) {
		if (iterator == nbrFiles)
			break;

		/*if (slave.get()->isAvailable()) {
			std::pair<std::string, Information> cmd = {files.at(iterator++), command.second};
			pid_t pid = fork();
			switch (pid) {
				case -1:
					// Throw a fork error;
				case 0:
					return;
				default:
					break;
			}
			slave.get()->addCommand(command);
		}*/
	}
}

int Plazza::calculateNewSlaves(int nbrFiles) const noexcept
{
	int newSlavesNeeded = nbrFiles;

	for (const auto &slave : _slaves) {
		// TODO: Check if slave is available
		//if (slave.get()->isAvailable())
		//	newSlavesNeeded--;
	}

	return nbrFiles;
}

std::vector<std::string> Plazza::split(const std::string &input, char delim) const noexcept
{
		std::istringstream string(input);
		std::string segment{};
		std::vector<std::string> seglist{};

		while(std::getline(string, segment, delim))
			seglist.emplace_back(segment);

		return seglist;
}

}
