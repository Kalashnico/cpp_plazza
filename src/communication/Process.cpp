//
// Created by Nicolas Guerin on 17/04/2018.
//

#include <Regex.hpp>
#include <csignal>
#include <zconf.h>
#include "Process.hpp"

namespace communication {

	Process::Process(int _nbThreads) : _nbThreads{_nbThreads}, _threads{}, _commands{}, _inactive{false}
	{
	}

	Process::~Process()
	{
	}

	bool Process::isAvailable() const noexcept
	{
		return _commands.size() < ((unsigned int)_nbThreads * 2);
	}

	void Process::addCommand(std::pair<std::string, Information> cmd) noexcept
	{
		_commands.push(cmd);
		if (_threads.size() < (unsigned int)_nbThreads) {
			createThread(_commands.front());
			_commands.pop();
		}
		_inactive = false;
		runProcess();
	}

	void Process::createThread(std::pair<std::string, Information> cmd) noexcept
	{
		parser::Regex	regex(cmd.first, cmd.second);
		_threads.emplace_back(regex.createThread());
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
			if (!_inactive)
				return;
			if ((clock()-start)/(double)(CLOCKS_PER_SEC) > 5.00) {
				kill(getpid(), SIGKILL);
			}
		}
	}
}
