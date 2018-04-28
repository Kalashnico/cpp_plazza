/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** ThreadPool
*/

#pragma once

#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "Plazza.hpp"
#include "Regex.hpp"

namespace communication {

class ThreadPool {
	public:
		ThreadPool(int threads);
		~ThreadPool();

		void enqueueTask(command);

	private:
		std::vector<std::thread> _threads;
		std::queue<command> _tasks;

		std::mutex _queueMutex;
		std::condition_variable condition;
		bool _stop;
};

}
