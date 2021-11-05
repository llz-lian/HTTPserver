#pragma once
#include <queue>
#include <memory>
#include <netinet/in.h>
#include "Event.hpp"
#include "Epoll.hpp"
#include "threadpool.hpp"
#include "StaticNums.hpp"
#include "Sub.hpp"

namespace NServer{
using namespace std;
using PEvent = shared_ptr<EVENT::Event>;
class Server
{
private:
    /* data */
    void awake();//awake blocks
    void choose();//choose a subthread to do doit(g)

    NEpoll::Epoll ep;//server epoll wait
    priority_queue<NSub::Sub> subq;//a queue save sub
    threadpool sub_pool;//sub do doit()
    threadpool accept_pool;//accept serverfd do accept()
    int server_fd;
    char buff[NUMS::MAX_BUFF];// or a string buffer
    sockaddr_in addr;
    epoll_event event;

    void addToSub(int fd);//add fd to sub epoll
    //createobj();
    PEvent createEvent(int fd);//create a event(fd)
public:
    Server(/* args */);
    void start();
    void mainLoop();
    ~Server();
};

}
