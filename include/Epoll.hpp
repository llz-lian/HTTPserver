#pragma once
#include <map>
#include <functional>
#include <memory>
#include <sys/epoll.h>
#include "threadpool.hpp"
#include "Event.hpp"
#include "Handle.hpp"
namespace NEpoll{
    using namespace std;
    class Epoll{
    //负责处理epoll等待的文件描述符
    private:

        Epoll(const Epoll &e) = delete;
        int epoll_fd;
        int num_wait_fd = 0;
        
        bool active = true;

        int MAX_FD;

        epoll_event ev;
    public:
        inline int getFd()const{
            return epoll_fd;
        };
        bool ctl(int ctl_flag,epoll_event & e,int fd){
            return epoll_ctl(epoll_fd,ctl_flag,fd,&e)==0;
        };
        inline bool addFd(int fd){
            if(num_wait_fd==MAX_FD)
                return false;
            ev.events = EPOLLIN|EPOLLOUT|EPOLLRDHUP|EPOLLET;
            if(!ctl(EPOLL_CTL_ADD,ev,fd))
            {
                //error
                return false;
            }
            ++num_wait_fd;
            return true;
        };
        inline void removeFD(int fd)
        {
            ctl(EPOLL_CTL_DEL,ev,fd);
            num_wait_fd--;
        };
        inline void modFd(int flags,int fd){
            ev.events = flags;
            if(!ctl(EPOLL_CTL_MOD,ev,fd))
            {

            }
        };

        inline int wait(vector<epoll_event> &events){
            return epoll_wait(epoll_fd,(epoll_event*)&events,events.size(),300);
        }

        inline int wait(epoll_event* events,int time_out = 3000)
        {
            return epoll_wait(epoll_fd,events,MAX_FD,time_out);
        }

        Epoll(int max_fd):MAX_FD(max_fd)
        {
            epoll_fd = epoll_create1(0);
            if(epoll_fd<=0)
            {
                //err
            }
        };
        ~Epoll(){};
    };
}