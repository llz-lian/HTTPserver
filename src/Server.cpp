#include "Server.hpp"
#include "Util.hpp"
using namespace NServer;



Server::Server(){
    server_fd = getListenfd(addr);
    ep.addFd(server_fd);
}

void Server::start()
{
    //do other
    mainLoop();
}

void Server::mainLoop()
{
    int fds = 0;
    while (true)
    {
        fds = epoll_wait(ep.getFd(),&event,1,500);
        if(event.data.fd != server_fd)
        {
            //wtf
            perror("<Server::mainLoop> waitfd error");
            exit(1);
        }else if(event.events&EPOLLIN)
        {
            //accept()
        }
        /* code */
    }
}