#pragma once

#include<vector>
#include<queue>
#include<thread>
#include<mutex>
#include<atomic>
#include<future>
#include<stdexcept>
#include<functional>
class threadpool
{
private:
	/* data */
	const int MAX_SIZE = 128;
	using Task = std::function<void()>;
	std::vector<std::thread> pool;
	std::queue<Task> tasks;
	std::mutex lock;
	std::condition_variable task_cv;
	std::atomic<bool> is_run{ true };
	std::atomic<int> idle{ 0 };
public:
	threadpool(size_t n = 16) {
		addThread(n);
	};
	void addThread(size_t n) {
		for (; pool.size() < MAX_SIZE&&n > 0; --n)
		{
			pool.emplace_back(
				[this]()
				{
					while (is_run)
					{
						Task task;
						{
							std::unique_lock<std::mutex> ulock{ lock };
							this->task_cv.wait(ulock, [this]() { return !is_run || !tasks.empty(); });
							if (!is_run && tasks.empty())
								return;//结束池子
							task = std::move(tasks.front());
							tasks.pop();
						}
						task();
					/* code */
				}
				}
			);
		}
	};
	template<class F, class... Args>
	auto commit(F && f, Args && ...args)->std::future<decltype(f(args...))> {
		using RetType = decltype(f(args...));
		auto task = std::make_shared<std::packaged_task<RetType()>>(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)//转发
			);
		std::future<RetType> future = task->get_future();
		{
			std::lock_guard<std::mutex> loc{ lock };
			tasks.emplace([task]() {(*task)(); });//lambda执行task构造
		}
		task_cv.notify_one();
		return future;
	}
	~threadpool() {
		is_run = false;
		task_cv.notify_all();
		for (std::thread & thread : pool)
		{
			if (thread.joinable())
			{
				thread.join();
			}
		}
	};
};