//
// Created by Nicolas Guerin on 23/04/2018.
//

#ifndef CPP_PLAZZA_REGEX_HPP
#define CPP_PLAZZA_REGEX_HPP

#include <vector>
#include <string>
#include <regex>
#include "Plazza.hpp"

#define REGEX_PHONE "(?:0)\\s*[0-9](?:[\\s]*\\d{2}){4}"
#define REGEX_EMAIL "(?:[a-z0-9!#$%&'*+\\=?^_`{|}~-]+(?:\\.[a-z0-9!#$%&'*+\\=?^_`{|}~-]+)*|\"(?:[\\x01-\\x08\\x0b\\x0c\\x0e-\\x1f\\x21\\x23-\\x5b\\x5d-\\x7f]|\\\\[\\x01-\\x09\\x0b\\x0c\\x0e-\\x7f])*\")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\\x01-\\x08\\x0b\\x0c\\x0e-\\x1f\\x21-\\x5a\\x53-\\x7f]|\\\\[\\x01-\\x09\\x0b\\x0c\\x0e-\\x7f])+)\\])\n"
#define REGEX_IP "((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)(\\.|$)){4}"

namespace parser {

class Regex {
	public:
		Regex(const std::string &_file, Information info);
		~Regex();

		void	parseFile() noexcept;
		std::vector<std::string>	parsePhone() const noexcept;
		std::vector<std::string>	parseEmail() const noexcept;
		std::vector<std::string>	parseIp() const noexcept;


		std::vector<std::string> getMatches() const noexcept { return  _matches; };

	private:
		std::string	_file;
		Information	_info;
		std::vector<std::string> _matches;

};

}

#endif //CPP_PLAZZA_REGEX_HPP
