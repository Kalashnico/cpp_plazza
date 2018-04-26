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
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "Plazza.hpp"
#include "Process.hpp"
#include "InternetSockets.hpp"
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

	if (bind(_masterSocket, (struct sockaddr *)&_server_addr, sizeof(_server_addr)) < 0)
		throw exceptions::BindError("Master socket failed to bind to port " +  std::to_string(PORT));

	listen(_masterSocket , 1000);
}

Plazza::~Plazza()
{
	checkDeadSlaves();
	for (auto &slave : _slaves)
		while (waitpid(slave.get()->getSlavePid(), nullptr, 0) != -1);
	close(_masterSocket);
}

void Plazza::setupCommand(command_t command)
{
	auto files = split(command.files, ' ');

	if (!doFilesExist(files)) {
		std::cout << "> One or more files do not exist" << std::endl;
		return;
	}

	checkDeadSlaves();

	auto nbrFiles = files.size();
	unsigned int iterator = 0;

	for (auto &slave : _slaves) {
		try {
			nbrFiles = sendCommandToSlave({files.at(iterator++), command.info}, slave.get()->getAcceptedSocket(), nbrFiles);
		} catch (exceptions::SendError e) {
		} catch (exceptions::RecieveError e) {}
	}

	for (unsigned int i = 0; i < nbrFiles; i++) {
		communication::InternetSockets iSocket(_masterSocket);
		int addrLen = sizeof(_server_addr);

		int slaveSocket = accept(_masterSocket, (struct sockaddr *)&_server_addr, (socklen_t *)&addrLen);
		if (slaveSocket < 0)
			throw exceptions::ConnectError("Failed to accept connection");

		_slaves.emplace_back(std::make_unique<communication::Process>(_maxThreads, iSocket));

		pid_t slavePid = fork();
		switch (slavePid) {
			case -1:
				throw exceptions::ForkError("Failed to fork slave");
				break;
			case 0:
				_slaves.back().get()->runProcess();
				return;
			default:
				_slaves.back().get()->setSlavePid(slavePid);
				_slaves.back().get()->setAcceptedSocket(slaveSocket);
				try {
					nbrFiles = sendCommandToSlave({files.at(iterator++), command.info}, _slaves.back().get()->getAcceptedSocket(), nbrFiles);
				} catch (exceptions::SendError e) {
				} catch (exceptions::RecieveError e) {}
				break;
		}
	}
}

int Plazza::sendCommandToSlave(command_t cmd, int socketClient, int nbrFiles)
{
	std::ostringstream oss;
	oss << cmd;
	std::string str(oss.str());

	if (send(socketClient, str.c_str(), str.size(), 0) < 0)
		throw exceptions::SendError("Failed to send a command to slave");

	nbrFiles = recieveSlaveStatus(nbrFiles, socketClient);
	return nbrFiles;
}

int Plazza::recieveSlaveStatus(int nbrFiles, int socketClient)
{
	char message[2];
	ssize_t readSize{};

	memset(message, 0, 2);
	readSize = recv(socketClient, message, 2, 0);

	if (readSize < 0)
		throw exceptions::RecieveError("Failed to recieve command");

	std::string smessage(message);
	if (smessage == "1")
		nbrFiles--;

	return nbrFiles;
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
		[](std::unique_ptr<communication::Process> &slave) { return waitpid(slave.get()->getSlavePid(), nullptr, WNOHANG) == slave.get()->getSlavePid(); }),
		_slaves.end());
}

std::vector<std::string> Plazza::split(const std::string &input, char delim) const noexcept
{
		std::istringstream string(input);
		std::string segment{};
		std::vector<std::string> seglist{};

		while (std::getline(string, segment, delim))
			seglist.emplace_back(segment);

		return seglist;
}

}

std::ostream &operator<<(std::ostream &out, const command_t &cmd)
{
	return out << cmd.files << ' ' << cmd.info;
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
