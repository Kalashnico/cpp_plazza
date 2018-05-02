/*
** EPITECH PROJECT, 2021
** cpp_plazza
** File description:
** Created by tclemenceau,
*/

#ifndef CPP_PLAZZA_LOGGER_HPP
#define CPP_PLAZZA_LOGGER_HPP

#include <string>
#include <vector>

namespace plazza {
	class Logger {
		public:
			Logger();
			~Logger();
			bool write(const std::vector<std::string> &to_send);
			std::vector<std::string> read() const;
		private:
			void makeLock() const;
			void removeLock() const;
			bool lockExist() const;
			long _first_line;
			std::string _filename;
			std::string _lockname;
	};
}

#endif //CPP_PLAZZA_LOGGER_HPP
