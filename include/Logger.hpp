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
			static Logger& getInstance()  { static Logger instance; return instance; }

			Logger(const Logger&) = delete;
			void operator=(const Logger&) = delete;

			bool write(const std::vector<std::string> &to_send) const;
			std::vector<std::string> read();

		private:
			Logger();
			~Logger();

			void makeLock() const;
			void removeLock() const;
			bool lockExist() const;

			long _first_line;

			std::string _filename;
			std::string _lockname;

	};
}

#endif //CPP_PLAZZA_LOGGER_HPP
