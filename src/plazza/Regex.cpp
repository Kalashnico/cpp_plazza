//
// Created by Nicolas Guerin on 23/04/2018.
//

#include "Regex.hpp"

Regex::Regex(const std::string &_file, Information info) : _file(_file), _info(info)
{

}

Regex::~Regex()
{

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


	return matches;
}

std::vector<std::string> Regex::parseEmail() const noexcept
{
	std::vector<std::string> matches{};

	return matches;
}

std::vector<std::string> Regex::parseIp() const noexcept
{
	std::vector<std::string> matches{};

	return matches;
}