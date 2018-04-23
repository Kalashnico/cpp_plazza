/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Shell
*/

#pragma once

#include <memory>
#include "Plazza.hpp"
#include "Parser.hpp"

namespace shell {

class Shell {
	public:
		Shell();
		~Shell();
		void run();

	private:
		void sendCommandToPlazza();

		std::unique_ptr<Plazza> _plazza;
		std::unique_ptr<parser::Parser> _parser;
};

}
