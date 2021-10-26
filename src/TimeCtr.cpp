#include "TimeCtr.hpp"


Time::Time_t Time::TimeCtr::now_time = std::chrono::steady_clock::now();
Time::Time_t Time::TimeCtr::pre_time = std::chrono::steady_clock::now();
Time::sysT Time::TimeCtr::sysclc = std::chrono::system_clock::now();
std::chrono::steady_clock::duration Time::TimeCtr::pre_to_now = Time::TimeCtr::now_time- Time::TimeCtr::now_time;