/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Shell
*/

#pragma once

#include <memory>
#include "Parser.hpp"

namespace shell {

class Shell {
	public:
		Shell();
		~Shell();

	private:
		std::unique_ptr<parser::Parser> _parser;
};

}
