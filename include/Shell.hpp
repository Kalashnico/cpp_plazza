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

namespace plazza {

class Shell {
	public:
		explicit Shell(int maxProcesses);
		~Shell();
		void run();

	private:
		void sendCommandToPlazza();

		std::unique_ptr<Plazza> _plazza;
		std::unique_ptr<parser::Parser> _parser;
};

}
