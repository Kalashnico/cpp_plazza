//
// Created by Nicolas Guerin on 17/04/2018.
//

#include <Regex.hpp>
#include <csignal>
#include <zconf.h>
#include "Process.hpp"

namespace communication {

	Process::Process(int nbThreads, const InternetSockets &iSocket) : _nbThreads{nbThreads}, _threads{}, _commands{}, _iSocket{iSocket}, _inactive{false}, _pid{}
	{
	}

	Process::~Process()
	{
	}

	void Process::createThread(command_t cmd) noexcept
	{
		//TODO: Check et send;
		parser::Regex	regex(cmd.files, cmd.info);
		_threads.emplace_back(std::thread(&parser::Regex::parseFile, regex));
	}

	void Process::runProcess() noexcept
	{
		for (auto &thread : _threads) {
			thread.join();
		}

		if (!_commands.empty()) {
			while (!_commands.empty() && _threads.size() < (unsigned int)_nbThreads) {
				createThread(_commands.front());
				_commands.pop();
			}
			runProcess();
			return;
		}

		_inactive = true;
		auto start = static_cast<int>(clock());
		while (true) {
			command_t cmd = _iSocket.receive();
			_commands.push(cmd);

			if (_commands.size() >= (_nbThreads * 2))
				_iSocket.sendToMaster(-1);
			else
				_iSocket.sendToMaster(1);
			if (!_inactive)
				return;
			if ((clock()-start)/(double)(CLOCKS_PER_SEC) > 5.00) {
				kill(getpid(), SIGKILL);
			}
		}
	}
}
