#include "Epoll.hpp"
#include "StaticNums.hpp"
using namespace NEpoll;


Epoll::Epoll()
{
    epoll_fd = epoll_create(NUMS::MAX_FD);
    if(epoll_fd<0)
    {
        perror("epoll create error");
        exit(1);
    }
}

bool Epoll::ctl(int flags,int fd)
{
    ev.data.fd = fd;
    ev.events=EPOLLIN|EPOLLET;
    if(epoll_ctl(epoll_fd,flags,fd,&ev))
    {
        perror("<Epoll::ctl> epoll_ctl");
        return false;
    }
    return true;
}