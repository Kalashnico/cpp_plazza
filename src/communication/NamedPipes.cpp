//
// Created by Nicolas Guerin on 17/04/2018.
//

#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <zconf.h>
#include "NamedPipes.hpp"


NamedPipes::NamedPipes() : _pipe(false)
{
	_filename = "/tmp/plazzapipe";
}

NamedPipes::~NamedPipes()
{
	unlink(_filename.c_str());
}

void NamedPipes::send(const std::string &to_send)
{
	std::ofstream file(_filename);

	if (!_pipe) {
		_pipe = true;
		mkfifo(_filename.c_str(), 0644);
	}
	file << to_send;
	file << std::endl;
	file.close();
	std::cout << "test" << std::endl;
}

std::string NamedPipes::receive()
{
	std::string to_return;
	std::ifstream file(_filename.data(), std::ios::in);

	std::getline(file, to_return);
	std::cout << "test2" << std::endl;
	file.close();
	return (to_return);
}