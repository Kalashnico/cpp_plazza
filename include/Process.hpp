//
// Created by Nicolas Guerin on 17/04/2018.
//

#pragma once

#include <string>
#include <thread>
#include <vector>
#include <queue>
#include "Plazza.hpp"

namespace communication {
	class Process {
		public:
			explicit Process(int _nbThreads);
			~Process();

			bool 	isAvailable() const noexcept;
			void	addCommand(std::pair<std::string, Information> cmd) noexcept;
			void	createThread(std::pair<std::string, Information> cmd) noexcept;
			void	runProcess() noexcept;
		private:
			int _nbThreads;
			std::vector<std::thread> _threads;
			std::queue<std::pair<std::string, Information>> _commands;
			bool _inactive;
	};
}
