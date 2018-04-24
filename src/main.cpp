/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Main
*/

#include <iostream>
#include <cstdlib>
#include "Shell.hpp"

void printUsage(const std::string &progname)
{
	std::cout << "Usage: " << progname << " [max_threads]" << std::endl;
}

bool isValidInt(char *str)
{
	while (*str) {
		if (!isdigit(*str++))
			return false;
	}
	return true;
}

int main(int ac, char **av)
{
	if (ac != 2)
		return printUsage(av[0]), 84;
	if (!isValidInt(av[1]))
		return printUsage(av[0]), 84;

	int maxThreads = std::stoi(std::string(av[1]));
	if (maxThreads <= 0)
		return printUsage(av[0]), 84;

	auto shell = std::make_unique<plazza::Shell>(maxThreads);
	shell->run();

	return 0;
}
