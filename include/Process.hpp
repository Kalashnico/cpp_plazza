//
// Created by Nicolas Guerin on 17/04/2018.
//

#pragma once

#include <string>
#include <thread>
#include <vector>
#include "Plazza.hpp"

namespace communication {
	class Process {
		public:
			Process(int _nbThreads, std::pair<std::string, Information> cmd);
			~Process();

			void	addCommand(std::pair<std::string, Information> cmd) noexcept { _commands.emplace_back(cmd); }

		private:
			int _nbThreads;
			std::vector<std::thread> _threads;
			std::vector<std::pair<std::string, Information>> _commands;

	};
}
