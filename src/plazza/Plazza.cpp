/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Main logic
*/

#include <iostream>
#include <sstream>
#include "Plazza.hpp"

Plazza::Plazza()
{}

Plazza::~Plazza()
{}

void Plazza::sendCommandToSlaves(std::pair<std::string, Information> command)
{
	std::vector<std::string> files = split(command.first, ' ');

	for (auto fileName : files)
		std::cout << fileName << std::endl;
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
