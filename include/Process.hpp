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

			void	createThread(command_t cmd) noexcept;
			void	runProcess() noexcept;
		private:
			int _nbThreads;
			std::vector<std::thread> _threads;
			std::queue<command_t> _commands;
			bool _inactive;
	};
}
