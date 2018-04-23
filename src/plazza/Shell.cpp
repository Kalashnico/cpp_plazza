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
}

Shell::~Shell()
{}

void Shell::run()
{
	std::string input = "";

	std::cout << "> ";
	while (std::getline(std::cin, input)) {
		try {
			_parser.get()->getCommands(input);
			sendCommandToPlazza();
		} catch(std::exception e) {
			std::cout << "Unkown command: " << input << std::endl;
		}
		std::cout << "> ";
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
