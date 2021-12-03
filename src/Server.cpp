#include "Server.hpp"
#include "Util.hpp"
using namespace std;

NServer::Server::Server(int thread_num,int sub_num):ep(100),addsub(thread_num)
{
    subs.resize(sub_num);
    listen_fd = getListenfd(addr);
    ep.addFd(listen_fd);
    stop = false;
    registSender();
}

void NServer::Server::start()
{
    for(auto & i:subs)
    {
        i.start();
    }
    while (!stop)
    {
        vector<epoll_event> ev;
        ev.resize(1);
        int rec = ep.wait(ev);

        int fd = ev[0].data.fd;
        auto events = ev[0].events;
        if(fd==listen_fd)
        {
            addsub.commit([this]{
                accpetFd();
            });
        }
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
    while(!subs[next_sub++].ep.addFd(client_fd))
    {
        if(next_sub>=sub_num)
        {
            next_sub = next_sub % sub_num;
        }
    }
    next_sub = next_sub % sub_num;
}