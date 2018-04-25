/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Main logic
*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <sys/socket.h>
#include <signal.h>
#include "Plazza.hpp"
#include "Process.hpp"
#include "Exceptions.hpp"

namespace plazza {

Plazza::Plazza(int maxThreads)
	: _maxThreads(maxThreads)
{
	_masterSocket = socket(AF_INET , SOCK_STREAM , 0);

	if (_masterSocket == -1)
		throw exceptions::SocketError("Creation of master socket failed");

	_server_addr.sin_family = AF_INET;
	_server_addr.sin_addr.s_addr = INADDR_ANY;
	_server_addr.sin_port = htons(PORT);

	if(bind(_masterSocket,(struct sockaddr *)&_server_addr , sizeof(_server_addr)) < 0)
		throw exceptions::BindError("Master socket failed to bind to port " + _server_addr.sin_port);

	listen(_masterSocket , 1000);
}

Plazza::~Plazza()
{
	close(_masterSocket);
}

void Plazza::setupCommand(command_t command)
{
	auto files = split(command.files, ' ');

	if (!doFilesExist(files)) {
		std::cout << "> One or more files do not exist" << std::endl;
		return;
	}

	auto nbrFiles = files.size();
	(void)nbrFiles;

	/*for (int i = 0; i < slavesToCreate; i++)
		_slaves.emplace_back(std::make_unique<communication::Process>(_maxThreads));
	*/

	//TODO: Implement
}

void Plazza::sendCommandToSlave(command_t cmd, int socketClient) const
{
	std::ostringstream oss;
	oss << cmd;
	std::string str(oss.str());

	if(send(socketClient , str.c_str() , str.size() , 0) < 0)
		throw exceptions::SendError("Failed to send a command to slave");
}

bool Plazza::doFilesExist(const std::vector<std::string> files) const noexcept
{
	for (auto fileName : files) {
		std::ifstream file(fileName);
		if (!file.good())
			return false;
	}
	return true;
}

void Plazza::checkDeadSlaves() noexcept
{
	_slaves.erase(std::remove_if(_slaves.begin(), _slaves.end(),
			[](std::unique_ptr<communication::Process> &_slave) { return kill(_slave.get()->getSlavePid(), 0) != 0; }),
			_slaves.end());
}

std::vector<std::string> Plazza::split(const std::string &input, char delim) const noexcept
{
		std::istringstream string(input);
		std::string segment{};
		std::vector<std::string> seglist{};

		while(std::getline(string, segment, delim))
			seglist.emplace_back(segment);

		return seglist;
}

}

std::ostream &operator<<(std::ostream &out, const command_t &cmd)
{
	out << cmd.files;
	out << cmd.info;
	return out;
}

std::istream &operator>>(std::istream &in, command_t &cmd)
{
	char info[1];
	in >> cmd.files;
	in >> info;

	switch (info[0]) {
		case '0':
			cmd.info = PHONE_NUMBER;
			break;
		case '1':
			cmd.info = EMAIL_ADDRESS;
			break;
		case '2':
			cmd.info = IP_ADDRESS;
			break;
		default:
			cmd.info = UNDEFINED;
			break;
	}
	return in;
}
