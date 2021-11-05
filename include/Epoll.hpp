#pragma once
#include <map>
#include <functional>
#include <memory>
#include <sys/epoll.h>
#include "threadpool.hpp"
#include "Event.hpp"
#include "Handle.hpp"
//也可以是一个Event,感觉没必要
namespace NEpoll{
    using namespace std;
    class Epoll{
    private:

        Epoll(const Epoll &e) = delete;
        int epoll_fd;
        bool active = true;
        epoll_event ev;
        bool ctl(int flags,int fd);
    public:
        inline int getFd()const{
            return epoll_fd;
        };
        void addFd(int fd){
            if(!ctl(EPOLL_CTL_ADD,fd))
            {
                perror("<Epoll::addFd> ctl error");
                exit(1);
            }
        };
        void removeFD(int fd);//while(active){sleep(MAX_WAIT_TIME);reomve(fd)}
        void modFd(int flags,int fd){
            
        };
        Epoll();
        ~Epoll();
    };
}