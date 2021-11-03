#pragma once

#include<vector>
#include<queue>
#include<thread>
#include<mutex>
#include<atomic>
#include<future>
#include<stdexcept>
#include<functional>
#include <iostream>
using std::endl;
class threadpool
{
private:
	/* data */
	const int MAX_SIZE = 128;
	const int MIN_SIZE = 16;
	using Task = std::function<void()>;
	std::vector<std::thread> pool;
	std::queue<Task> tasks;
	std::mutex lock;
	std::condition_variable task_cv;
	std::atomic<bool> is_run{ true };
	std::atomic<int> idle{ 0 };
	std::atomic<bool> drop{ false };
	std::atomic<int> drop_num{0};
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
						idle--;
						task();
						if(drop&&drop_num>0)
						{
							drop_num--;
							return;
						}
						idle++;
						
					/* code */
					}
				}
			);
			idle++;
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
		//grow();
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

	void grow()
	{
		if(tasks.size()>pool.size()*1.5)
		{
			addThread(pool.size());
		}
		else if(pool.size()>tasks.size())
		{
			drop_num = (pool.size() - tasks.size()) * 2 / 3;
			if(pool.size()-drop_num<MIN_SIZE)
				return;
			drop = true;
			for (std::thread & thread : pool)
			{
				if (thread.joinable())
				{
					thread.join();
				}
				
			}
			drop_num = 0;
			drop = false;
		}
		
	}

	void restart(){
		int n = pool.size();
		if(tasks.empty())
		{
			is_run = false;
			task_cv.notify_all();
			for (std::thread & thread : pool)
			{
				if (thread.joinable())
				{
					thread.join();
				}
			}
			is_run = true;
			addThread(n);
			std::cout<<"restart thread"<<std::endl;
		}
	}
	void showPoolStat()
	{
		std::cout<<"Task num:"<<tasks.size()<<std::endl;
		std::cout<<"Thread num:"<<pool.size()<<std::endl;
		std::cout<<"Thread idle:"<<idle<<std::endl<<std::endl;
	}

};