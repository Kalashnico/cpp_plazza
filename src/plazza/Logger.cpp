/*
** EPITECH PROJECT, 2021
** cpp_plazza
** File description:
** Created by tclemenceau,
*/

#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include "Logger.hpp"

namespace plazza {

	Logger::Logger() : _first_line(0)
	{
		std::time_t now =  std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		char buf[100] = {0};
		std::strftime(buf, sizeof(buf), "%Y-%m-%d-%T", std::localtime(&now));

		std::string dateStr(buf);
		std::ostringstream filename;
		std::ostringstream lockname;
		filename << "output_plazza-" << dateStr << ".log";
		lockname << ".output_plazza-" << dateStr << ".log.lock";

		_filename = filename.str();
		_lockname = lockname.str();
	}

	std::vector<std::string> Logger::read()
	{
		std::vector<std::string> received;

		while (!lockExist())
			return received;

		makeLock();
		std::ifstream file(_filename);
		std::string tmp;
		for (int i = 0 ; i < _first_line; i++)
			std::getline(file, tmp, '\n');
		while (std::getline(file, tmp, '\n')) {
			_first_line++;
			received.emplace_back(tmp);
		}

		file.close();
		removeLock();
		return received;
	}

	bool Logger::write(const std::vector<std::string> &to_send) const
	{
		while (!lockExist());
		makeLock();

		std::ofstream file(_filename, std::ios_base::app | std::ios_base::out);
		if (!file.good()) {
			file.close();
			removeLock();
			return false;
		}

		for (const auto &line : to_send)
			file << line << std::endl;
		file.close();
		removeLock();
		return true;
	}

	bool Logger::lockExist() const
	{
		std::ifstream file(_lockname.c_str());

		return !file.good();
	}

	void Logger::makeLock() const
	{
		std::ofstream lock(_lockname.c_str());

		lock << std::endl;
		lock.close();
	}

	void Logger::removeLock() const
	{
		remove(_lockname.c_str());
	}

	Logger::~Logger() = default;
}