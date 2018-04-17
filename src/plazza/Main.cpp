/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Main
*/

#include <iostream>
#include <cstdlib>

void printUsage(std::string progname)
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
	int maxProcesses = atoi(av[1]);
	if (maxProcesses <= 0)
		return printUsage(av[0]), 84;
	return 0;
}
