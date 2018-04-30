/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Shell for commands
*/

#include <iostream>
#include "Shell.hpp"
#include "Exceptions.hpp"

namespace plazza {

Shell::Shell(int maxProcesses)
	: _exit(false)
{
	try {
		_plazza = std::make_unique<Plazza>(maxProcesses);
	} catch (exceptions::PlazzaError e) {
		std::cout << e.what() << std::endl;
		_exit = true;
		return;
	}

	_parser = std::make_unique<parser::Parser>();

	_cmds["clear"] = &Shell::clear;
	_cmds["exit"] = &Shell::exit;
}

Shell::~Shell()
{}

void Shell::clear() noexcept
{
	std::cout << "\033[H\033[J";
}

void Shell::exit() noexcept
{
	_exit = true;
}

void Shell::run()
{
	std::string input = "";

	while (!_exit && std::getline(std::cin, input)) {
		if (_cmds.find(input) != _cmds.end()) {
			(this->*_cmds[input])();
			continue;
		}

		try {
			_parser.get()->getCommands(input);
			sendCommandToMaster();
		} catch(std::exception e) {
			std::cout << "> Bad command: " << input << std::endl;
			_exit = true;
		}
	}
}

void Shell::sendCommandToMaster() noexcept
{
	auto command = _parser.get()->getNextCommand();

	while (command.info != UNDEFINED) {
		int status = _plazza.get()->setupCommand(command);
		if (status == 1) {
			_exit = true;
			return;
		}
		command = _parser.get()->getNextCommand();
	}
}

}
