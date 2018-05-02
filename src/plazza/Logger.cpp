/*
** EPITECH PROJECT, 2021
** cpp_plazza
** File description:
** Created by tclemenceau,
*/

#include <fstream>
#include "Logger.hpp"

namespace plazza {

	Logger::Logger() : _first_line(0), _filename("output_plazza.log"),
		_lockname(".output_plazza.log.lock")
	{
	}

	std::vector<std::string> Logger::read() const
	{
		std::vector<std::string> received;
		if (!lockExist())
			return received;
		makeLock();
		std::ifstream file(_filename);
		std::string tmp;
		for (int i = 0 ; i < _first_line ; i++)
			std::getline(file, tmp, '\n');
		while (std::getline(file, tmp, '\n'))
			received.emplace_back(tmp);
		file.close();
		removeLock();
		return received;
	}

	bool Logger::write(const std::vector<std::string> &to_send)
	{
		while (!lockExist());
		std::ofstream file(_filename);

		if (!file.good())
			return false;
		makeLock();
		for (const auto &line : to_send) {
			_first_line += 1;
			file << line << std::endl;
		}
		file.close();
		removeLock();
		return true;
	}

	bool Logger::lockExist() const
	{
		std::ifstream file(_lockname.c_str());

		return file.good();
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