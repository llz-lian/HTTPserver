#pragma once
#include <chrono>
#include "memory"
#include "Http.hpp"
#include "StaticNums.hpp"
namespace NEvent{
    enum STATUS{
        WAITREAD,
        WAITSEND,
        TIMEOUT,
        ERR
    };
    enum ERRNUM{
        READ_ERR,
        WRITE_ERR,
        HTTP_ERR
    };
    using namespace std;
    class Event
    {
    public:
        void updateTime();
        shared_ptr<NHTTP::Http> http;
        Event(int fd);
        ~Event();
        inline uint getStatus() const{return status;};
        inline int getFd() const{return fd;};
        inline void changeStatus(uint status){this->status = status;};
        inline void setErr(uint ERR){err = ERR;};

        bool timeOut(){
            return pre_to_now.count()>=NUMS::TIME_OUT;
        }
    private:
        chrono::steady_clock::time_point now_time;
        chrono::steady_clock::time_point start_time;
        chrono::steady_clock::duration pre_to_now;

        int fd;
        uint status;
        uint err;
    };
};