#pragma once

#include <iostream>
#include <chrono>
#include <string>
namespace Time {
	using namespace std;
	inline const time_t covTime(const chrono::system_clock::time_point& t) {
		return chrono::system_clock::to_time_t(t);
	};
	using Time_t = chrono::steady_clock::time_point;
	using sysT = chrono::system_clock::time_point;
	class TimeCtr
	{
	/*
		求时间段：get() /操作/  get() showdiff()
		当前时间：get().showNowTime();
	*/
	public:
		inline static TimeCtr& get()
		{
			static TimeCtr time;
			TimeCtr::pre_time = TimeCtr::now_time;
			TimeCtr::now_time = chrono::steady_clock::now();
			TimeCtr::pre_to_now = TimeCtr::now_time - TimeCtr::pre_time;
			TimeCtr::sysclc = chrono::system_clock::now();
			return time;
		}
		inline void showNowTime()const
		{
			cout << "now time:" << getTime() << endl;
		};

		template<class T = chrono::milliseconds>
		inline void showdiff()const
		{
			cout << "diff:" << chrono::duration_cast<T>(TimeCtr::pre_to_now).count()<<endl;
		};

		inline static string getTime()
		{
			const time_t&& a = covTime(TimeCtr::sysclc);
			return string(ctime(&a));
		};
		template<class T = chrono::milliseconds>
		inline static string getDur()
		{
			return to_string(chrono::duration_cast<T>(TimeCtr::pre_to_now).count())<<endl;
		};
	private:
		TimeCtr() {};
		~TimeCtr() {};
		TimeCtr(const TimeCtr& t) = delete;
		static sysT sysclc;
		static Time_t pre_time;
		static Time_t now_time;
		static chrono::steady_clock::duration pre_to_now;

		friend const time_t covTime(const sysT& t);

	};
};
#pragma once
