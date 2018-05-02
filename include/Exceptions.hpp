/*
** EPITECH PROJECT, 2018
** Arcade core
** File description:
** Exceptions
*/

#pragma once

#include <string>

namespace exceptions {

class PlazzaError : public std::exception
{
	public:
		PlazzaError(const std::string &message);
		virtual ~PlazzaError() noexcept = default;

		const char *what() const noexcept;
	private:
		std::string _message;
};

class ForkError : public PlazzaError
{
	public:
		ForkError(const std::string &message);
};

class SocketError : public PlazzaError
{
	public:
		SocketError(const std::string &message);
};

class BindError : public PlazzaError
{
	public:
		BindError(const std::string &message);
};

class ConnectError : public PlazzaError
{
	public:
		ConnectError(const std::string &message);
};

class SendError : public PlazzaError
{
	public:
		SendError(const std::string &message);
};

class RecieveError : public PlazzaError
{
	public:
		RecieveError(const std::string &message);
};

class EnqueueError : public PlazzaError
{
	public:
		EnqueueError(const std::string &message);
};

class FileError : public PlazzaError
{
	public:
		FileError(const std::string &message);
};

class CommandError : public PlazzaError
{
	public:
		CommandError(const std::string &message);
};

}
