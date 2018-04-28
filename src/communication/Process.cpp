//
// Created by Nicolas Guerin on 17/04/2018.
//

#include <csignal>
#include <zconf.h>
#include "Process.hpp"
#include "Regex.hpp"

namespace communication {

	Process::Process(int nbThreads, const InternetSockets &iSocket)
		: _nbThreads{nbThreads}, _threads{}, _commands{}, _iSocket{iSocket}, _pid{}, _acceptedSocket{}
	{
		//TODO: Thread pool
	}

	Process::~Process()
	{}

	void Process::createThread(command cmd) noexcept
	{
		parser::Regex regex(cmd.files, cmd.info);
		_threads.emplace_back(std::thread(&parser::Regex::parseFile, regex));
	}

	void Process::runProcess() noexcept
	{
		for (auto &thread : _threads)
			thread.join();

		if (!_commands.empty()) {
			while (!_commands.empty() && _threads.size() < (unsigned int)_nbThreads) {
				createThread(_commands.front());
				_commands.pop();
			}
			runProcess();
			return;
		}

		unsigned int inactiveSeconds = 0;
		while (true) {
			if (_iSocket.canReceive()) {
				command cmd = _iSocket.receive();

				if (_commands.size() >= (unsigned int)(_nbThreads * 2) || cmd.info == UNDEFINED) {
					_iSocket.sendToMaster(-1);
				} else {
					_iSocket.sendToMaster(1);
					_commands.emplace(cmd);
					runProcess();
					return;
				}
			} else
				inactiveSeconds++;

			if (inactiveSeconds >= 5)
				return;
		}
	}
}
