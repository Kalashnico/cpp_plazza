//
// Created by Nicolas Guerin on 17/04/2018.
//

#include "Process.hpp"

namespace communication {

	Process::Process(int _nbThreads, std::pair<std::string, Information> cmd) : _nbThreads{_nbThreads}, _threads{}, _commands{}
	{
		_commands.emplace_back(cmd);

	}

	Process::~Process()
	{

	}
}
