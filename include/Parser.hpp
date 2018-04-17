//
// Created by Nicolas Guerin on 17/04/2018.
//

#pragma once

#include <string>
#include <queue>

namespace parser {

	enum Information {
		PHONE_NUMBER,
		EMAIL_ADDRESS,
		IP_ADDRESS
	};

	class Parser {
		public:
			Parser();
			~Parser();

			std::string getInput() const noexcept;
			void	getCommands();
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
