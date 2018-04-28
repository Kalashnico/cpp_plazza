/*
** EPITECH PROJECT, 2018
** Arcade core
** File description:
** Exceptions
*/

#include "Exceptions.hpp"

namespace exceptions {

PlazzaError::PlazzaError(const std::string &message)
	: _message(message)
{}

ForkError::ForkError(const std::string &message)
	: PlazzaError("Fork Exception: " + message)
{}

SocketError::SocketError(const std::string &message)
	: PlazzaError("Socket Exception: " + message)
{}

BindError::BindError(const std::string &message)
	: PlazzaError("Bind Exception: " + message)
{}

ConnectError::ConnectError(const std::string &message)
	: PlazzaError("Connect Exception: " + message)
{}

SendError::SendError(const std::string &message)
	: PlazzaError("Send Exception: " + message)
{}

RecieveError::RecieveError(const std::string &message)
	: PlazzaError("Recieve Exception: " + message)
{}

EnqueueError::EnqueueError(const std::string &message)
	: PlazzaError("Enqueue Exception: " + message)
{}

const char *PlazzaError::what() const noexcept
{
	return _message.c_str();
}

}
