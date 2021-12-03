#include "Epoll.hpp"
using namespace NEpoll;

Epoll::Epoll(int max_fd):MAX_FD(max_fd)
{
    epoll_fd = epoll_create1(0);
    if(epoll_fd<=0)
    {
        //err
    }
}

Epoll::~Epoll()
{
    //delete all fd
}