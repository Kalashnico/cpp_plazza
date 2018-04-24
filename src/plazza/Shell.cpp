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
	: _exit(false)
{
	_plazza = std::make_unique<Plazza>(maxProcesses);
	_parser = std::make_unique<parser::Parser>();

	_cmds["clear"] = std::bind(&Shell::clear, this);
	_cmds["exit"] = std::bind(&Shell::exit, this);
}

Shell::~Shell()
{}

void Shell::clear()
{
	std::cout << "\033[H\033[J";
}

void Shell::exit()
{
	_exit = true;
}

void Shell::run()
{
	std::string input = "";

	while (!_exit && std::getline(std::cin, input)) {
		if (_cmds.find(input) != _cmds.end()) {
			_cmds[input]();
			continue;
		}

		try {
			_parser.get()->getCommands(input);
			sendCommandToPlazza();
		} catch(std::exception e) {
			std::cout << "> Unkown command: " << input << std::endl;
		}
	}
}

void Shell::sendCommandToPlazza() const noexcept
{
	auto command = _parser.get()->getNextCommand();

	while (command.info != UNDEFINED) {
		_plazza.get()->sendCommandToSlaves(command);
		command = _parser.get()->getNextCommand();
	}
}

}
