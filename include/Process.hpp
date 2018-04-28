//
// Created by Nicolas Guerin on 17/04/2018.
//

#pragma once

#include <string>
#include <vector>
#include <queue>
#include "Plazza.hpp"
#include "InternetSockets.hpp"
#include "ThreadPool.hpp"

namespace communication {
	class Process {
		public:
			Process(int nbThreads, const InternetSockets &iSocket);
			~Process();

			void	addTask(command cmd) const noexcept;
			void	runProcess() noexcept;

			void 	setSlavePid(pid_t pid) noexcept { _pid = pid; }
			pid_t 	getSlavePid() const noexcept { return _pid; }

			void	setAcceptedSocket(int socket) noexcept { _acceptedSocket = socket; }
			int	getAcceptedSocket() const noexcept { return _acceptedSocket; }

			void	incrementRecievedCommands() noexcept { _recievedCommands++; }
			int	getRecievedCommands() const noexcept { return _recievedCommands; }

		private:
			int _recievedCommands;

			int _nbThreads;
			std::unique_ptr<ThreadPool> _threadPool;

			InternetSockets	_iSocket;
			pid_t _pid;
			int _acceptedSocket;
	};
}
