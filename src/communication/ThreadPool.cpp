/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** TheadPool
*/

#include "ThreadPool.hpp"
#include "Exceptions.hpp"

namespace communication {

ThreadPool::ThreadPool(int threads)
	: _stop{false}
{
	for (int i = 0; i < threads; i++) {
		_threads.emplace_back(
			[this] {
				while (true) {

					command cmd {"", UNDEFINED};

					{
						std::unique_lock<std::mutex> lock(this->_queueMutex);
						this->condition.wait(lock, [this] {
							return this->_stop || !this->_tasks.empty();
						});

						if (this->_stop && this->_tasks.empty())
							return;

						cmd = this->_tasks.front();
						this->_tasks.pop();
					}

					parser::Regex regex(cmd.files, cmd.info);
					regex.parseFile();
				}
			}
		);
	}
}

ThreadPool::~ThreadPool()
{
	{
		std::unique_lock<std::mutex> lock(_queueMutex);
		_stop = true;
	}
	condition.notify_all();

	for (auto &thread : _threads)
		thread.join();
}

void ThreadPool::enqueueTask(command cmd)
{
	{
		std::unique_lock<std::mutex> lock(_queueMutex);

		if (_stop)
			throw exceptions::EnqueueError("ThreadPool is stopped");

		_tasks.emplace(cmd);
	}
	condition.notify_one();
}

}
