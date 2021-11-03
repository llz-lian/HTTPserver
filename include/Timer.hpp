#pragma once
#include <chrono>
#include <thread>

class Timer
{
public:
	template<class T>
	void setTimeOut(T fuc, int delay)
	{
		std::thread t([=] {
			std::this_thread::sleep_for(std::chrono::seconds(delay));
			fuc();
			});
		t.detach();
	};
};

