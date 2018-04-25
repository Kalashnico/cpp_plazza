//
// Created by Nicolas Guerin on 17/04/2018.
//

#pragma once

#include <string>
#include <thread>
#include <vector>
#include <queue>
#include "Plazza.hpp"
#include "InternetSockets.hpp"

namespace communication {
	class Process {
		public:
			Process(int nbThreads, const InternetSockets &iSocket);
			~Process();

			void	createThread(command_t cmd) noexcept;
			void	runProcess() noexcept;
			void 	setSlavePid(pid_t pid) noexcept { _pid = pid; }
			pid_t 	getSlavePid() const noexcept { return _pid; }
			InternetSockets getISocket() const noexcept {return _iSocket; }

		private:
			int _nbThreads;
			std::vector<std::thread> _threads;
			std::queue<command_t> _commands;
			InternetSockets	_iSocket;
			bool _inactive;
			pid_t _pid;
	};
}
