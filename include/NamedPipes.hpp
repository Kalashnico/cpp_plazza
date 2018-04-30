//
// Created by Nicolas Guerin on 17/04/2018.
//

#pragma once

#include <string>

class NamedPipes {
	public:
		NamedPipes();
		~NamedPipes();
		void send(const std::string &to_send);
		std::string receive();
	private:
		std::string _filename;
		bool _pipe;
};