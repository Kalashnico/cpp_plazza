/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Shell
*/

#pragma once

#include <memory>
#include <map>
#include "Plazza.hpp"
#include "Parser.hpp"

namespace plazza {

class Shell {
	public:
		explicit Shell(int maxProcesses);
		~Shell();
		void run();

	private:
		void sendCommandToMaster() noexcept;
		void logCheck() noexcept;
		void clear() noexcept;
		void exit() noexcept;

		bool _master;
		bool _exit;

		std::unique_ptr<Plazza> _plazza;
		std::unique_ptr<parser::Parser> _parser;
		std::map<std::string, void (plazza::Shell::*)() noexcept> _cmds;
};

}
