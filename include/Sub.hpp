#pragma once
#include <vector>
#include "Event.hpp"
#include "threadpool.hpp"
#include "Epoll.hpp"
#include "StaticNums.hpp"
#include "Http.hpp"
namespace NSub{
using namespace std;
using PEvent = shared_ptr<EVENT::Event>;
class Core{
private:
    HTTP::Http http;
public:
    void doit(PEvent & event)
    {
        
    }
    Core(string & request):http(request){
    };
};


class Sub
{
private:
    /* data */
    vector<PEvent> events;
    epoll_event evs[NUMS::MAX_EVENTS];
    int wake_fd;

    threadpool to_doit;
    NEpoll::Epoll ep;
public:
    Sub(/* args */);
    void start();
    void awake();
    inline void addEvents(PEvent & event){
        events[event->getFd()] = event;
    };
    inline int getWakeFd()const{
        return wake_fd;
    };

    ~Sub();
};

}