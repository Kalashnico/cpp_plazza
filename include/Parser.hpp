//
// Created by Nicolas Guerin on 17/04/2018.
//

#pragma once

#include <string>
#include <queue>
#include "Plazza.hpp"

namespace parser {

	class Parser {
		public:
			Parser();
			~Parser();

			void getCommands(const std::string &input);
			Information stringToInfo(const std::string &input) const noexcept;
			std::vector<std::string> splitString(const std::string &input) const noexcept;

			//Errors
			bool commandErrors(const std::vector<std::string> &tokens) const noexcept;

			//Getter
			std::pair<std::string, Information> getNextCommand() noexcept;

		private:
			std::queue<std::string> _files;
			std::queue<Information>	_info;

	};
}
