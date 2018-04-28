//
// Created by Nicolas Guerin on 17/04/2018.
//

#include <csignal>
#include <zconf.h>
#include "Process.hpp"
#include "Regex.hpp"
#include "Exceptions.hpp"

namespace communication {

	Process::Process(int nbThreads, const InternetSockets &iSocket)
		: _nbThreads{nbThreads}, _commands{}, _threadPool{nullptr}, _iSocket{iSocket}, _pid{}, _acceptedSocket{}
	{}

	Process::~Process()
	{}

	void Process::addTask(command cmd) noexcept
	{
		try {
			_threadPool.get()->enqueueTask(cmd);
		} catch (exceptions::EnqueueError e) {}
	}

	void Process::runProcess() noexcept
	{
		if (_threadPool == nullptr)
			_threadPool = std::make_unique<ThreadPool>(_nbThreads);

		if (!_commands.empty()) {
			while (!_commands.empty()) {
				addTask(_commands.front());
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
