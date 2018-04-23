/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Shell for commands
*/

#include <iostream>
#include "Shell.hpp"

namespace plazza {

Shell::Shell(int maxProcesses)
{
	_plazza = std::make_unique<Plazza>(maxProcesses);
	_parser = std::make_unique<parser::Parser>();
	sendCommandToPlazza();
}

Shell::~Shell()
{}

void Shell::run()
{
	std::string input = "";

	while (std::getline(std::cin, input)) {
		_parser.get()->getCommands(input);
		sendCommandToPlazza();
	}
}

void Shell::sendCommandToPlazza()
{
	auto command = _parser.get()->getNextCommand();

	while (command.second != UNDEFINED) {
		_plazza.get()->sendCommandToSlaves(command);
		command = _parser.get()->getNextCommand();
	}
}

}
