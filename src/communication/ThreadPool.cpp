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
	for (int i = 0; i < threads; i++)
		_working.emplace_back(false);

	for (int i = 0; i < threads; i++) {
		_threads.emplace_back(
			[this, i] {
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

					{
						std::unique_lock<std::mutex> lock(this->_queueMutex);
						_working[i] = true;
					}

					parser::Regex regex(cmd.files, cmd.info);
					regex.parseFile();

					{
						std::unique_lock<std::mutex> lock(this->_queueMutex);
						_working[i] = false;
					}
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

int ThreadPool::getTasksAmount() noexcept
{
	std::unique_lock<std::mutex> lock(_queueMutex);

	int amount = _tasks.size();
	for (auto isWorking : _working)
		if (isWorking)
			amount++;

	return amount;
}

bool ThreadPool::isWorking() noexcept
{
	std::unique_lock<std::mutex> lock(this->_queueMutex);

	for (auto isWorking : _working)
		if (isWorking)
			return true;

	return false;
}

}
