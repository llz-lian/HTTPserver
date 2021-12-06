#include "Server.hpp"
#include "Util.hpp"
using namespace std;

NServer::Server::Server(int thread_num,int sub_num):ep(100),addsub(thread_num)
{
    for(int i = 0;i<sub_num;i++)
    {
        NSub::Sub * sub = new NSub::Sub();
        subs.push_back(sub);
    }
    listen_fd = getListenfd(addr);
    ep.addFd(listen_fd);
    epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = listen_fd;
    ep.ctl(EPOLL_CTL_ADD,ev,listen_fd);

    printf("epollfd:%d,listen:%d\n",ep.getFd(),listen_fd);

    stop = false;
    registSender();
}

void NServer::Server::start()
{
    for(auto & i:subs)
    {
        addsub.commit([&]{
            i->start();
        });
    }

    epoll_event ev;
    while (!stop)
    {
        int rec = ep.wait(&ev,-1);
        int fd = ev.data.fd;
        auto events = ev.events;
        printf("accept!\n");
        
        accpetFd();
        
    }
    //log error
}

void NServer::Server::accpetFd()
{
    sockaddr_in client;
    socklen_t slen = sizeof(client);

    int client_fd = accept(listen_fd,(sockaddr *)&client,&slen);
    if(client_fd<0)
        return;
    while(!subs[next_sub++]->ep.addFd(client_fd))
    {
        if(next_sub>=sub_num)
        {
            next_sub = next_sub % sub_num;
        }
    }
    next_sub = next_sub % sub_num;
}
NServer::Server::~Server()
{
    for(int i = 0;i<sub_num;i++)
    {
        delete &subs[i];
    }
}