/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Shell for commands
*/

#include <iostream>
#include "Shell.hpp"

namespace shell {

Shell::Shell()
{
	_parser = std::make_unique<parser::Parser>();

	auto command = _parser.get()->getNextCommand();
	while (command.second != 0) {
		auto command = _parser.get()->getNextCommand();
		std::cout << command.first << std::endl;
		std::cout << command.second << std::endl;
	}
}

Shell::~Shell()
{}

}
