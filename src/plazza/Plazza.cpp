/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Main logic
*/

#include <iostream>
#include "Plazza.hpp"

Plazza::Plazza()
{}

Plazza::~Plazza()
{}

void Plazza::sendCommandToSlaves(std::pair<std::string, Information> command)
{
	(void) command;
	std::cout << "Command recieved: files: " << command.first << " enum type: " << command.second << std::endl;
}
