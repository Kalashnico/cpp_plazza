//
// Created by Nicolas Guerin on 17/04/2018.
//

#include <iostream>
#include <sstream>
#include "Parser.hpp"

namespace parser {
	Parser::Parser() : _files{}, _info{}
	{
		getCommands();
	}

	Parser::~Parser()
	{

	}

	std::string Parser::getInput() const noexcept
	{
		std::string input{};

		std::getline(std::cin, input);

		return input;
	}

	bool Parser::commandErrors(const std::vector<std::string> &tokens) const noexcept
	{
		size_t countInfo{};

		for (auto const &token : tokens) {
			if (token == "PHONE_NUMBER" || token == "EMAIL_ADDRESS" || token == "IP_ADDRESS")
				++countInfo;
		}
		return countInfo != 1;
	}

	std::vector<std::string> Parser::splitString(const std::string &input) const noexcept
	{
		std::istringstream string(input);
		std::string segment;
		std::vector<std::string> seglist;

		while(std::getline(string, segment, ';'))
		{
			seglist.emplace_back(segment);
		}
		return seglist;
	}

	void Parser::getCommands()
	{
		auto input = getInput();

		auto inputSplited = splitString(input);

		for (auto const &s : inputSplited) {
			std::istringstream iss(s);
			std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
						      std::istream_iterator<std::string>{}};

			if (tokens.size() <= 1 || commandErrors(tokens))
				throw std::invalid_argument("Command line invalid");

			auto info = tokens.back();
			_info.push(stringToInfo(info));

			tokens.pop_back();

			std::string	files{};
			for (auto const &tok : tokens) {
				files += tok + " ";
			}

			_files.push(files);
		}

	}

	Information Parser::stringToInfo(const std::string &input) const noexcept
	{
		if (input == "PHONE_NUMBER")
			return PHONE_NUMBER;
		else if (input == "EMAIL_ADDRESS")
			return EMAIL_ADDRESS;
		else
			return IP_ADDRESS;
	}

	std::pair<std::string, Information> Parser::getNextCommand() noexcept
	{
		std::pair<std::string, Information> command;


		command.first = _files.front();
		_files.pop();

		command.second = _info.front();
		_info.pop();

		return command;
	}

}
