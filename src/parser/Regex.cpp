//
// Created by Nicolas Guerin on 23/04/2018.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "Regex.hpp"

namespace parser {

	Regex::Regex(const std::string &_file, Information info) : _file{_file}, _info{info}, _buffer{}, _matches{}
	{
		openFile();
	}

	Regex::~Regex()
	{

	}


	void Regex::openFile()
	{
		std::ifstream file(_file);
		std::stringstream mapStream{};
		if (file.is_open()) {
			mapStream << file.rdbuf();
			file.close();
		}
		else {
			throw std::invalid_argument("Invalid file: " + _file + ".");
		}
		std::getline(mapStream, _buffer);
	}


	void Regex::parseFile() noexcept
	{
		switch (_info) {
			case PHONE_NUMBER:
				_matches = parsePhone();
				break;
			case EMAIL_ADDRESS:
				_matches = parseEmail();
				break;
			case IP_ADDRESS:
				_matches = parseIp();
				break;
			default:
				break;
		}

	}

	std::vector<std::string> Regex::parsePhone() const noexcept
	{
		std::vector<std::string> matches{};
		const std::regex regx(REGEX_PHONE);
		std::smatch sm{};

		std::string copy(_buffer);

		while (std::regex_search(copy, sm, regx))
		{
			matches.emplace_back(sm.str());
			copy = sm.suffix();

		};

		return matches;
	}

	std::vector<std::string> Regex::parseEmail() const noexcept
	{
		std::vector<std::string> matches{};
		const std::regex regx(REGEX_EMAIL);
		std::smatch sm{};

		std::string copy(_buffer);

		while (std::regex_search(copy, sm, regx))
		{
			matches.emplace_back(sm.str());
			copy = sm.suffix();

		};

		return matches;
	}

	std::vector<std::string> Regex::parseIp() const noexcept
	{
		std::vector<std::string> matches{};
		const std::regex regx(REGEX_IP);
		std::smatch sm{};

		std::string copy(_buffer);

		while (std::regex_search(copy, sm, regx))
		{
			if (sm.str().length() > 4)
				matches.emplace_back(sm.str());
			copy = sm.suffix();

		};

		return matches;
	}

	std::thread Regex::createThread()
	{
		return std::thread(&Regex::parseFile, this);
	}

}
