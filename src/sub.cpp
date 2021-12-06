#include "Sub.hpp"

NSub::Sub::Sub():ep(MAX_FD)
{
    ep_events = new epoll_event[MAX_FD];
};

void NSub::Sub::addMap(int fd)
{
    if(fd<0)
        return;
    fd_map[fd] = new NEvent::Event(fd);
}

int NSub::Sub::addSubDo()
{
    int num = ep.wait(ep_events,-1);
    for(int i = 0;i<num;i++)
    {
        int fd = ep_events[i].data.fd;
        int event = ep_events[i].events;
        if(fd_map.find(fd)==fd_map.end())
        {
            addMap(fd);
        }
        doit.commit([&]{
            processing(*fd_map[fd],event);
        });
    }
    return num!=0;
}

void NSub::Sub::processing(NEvent::Event & ev,uint flags)
{
    char buf[1024];
    if(ev.getStatus()==NEvent::STATUS::TIMEOUT||(flags&(EPOLLRDHUP|EPOLLERR)))
    {
        
    }
    else if(ev.getStatus()==NEvent::STATUS::WAITREAD&&(flags&EPOLLIN))
    {
        ev.updateTime();
        int ret = readData(ev.getFd(),buf);
        if(ret < 0)
        {
            ev.changeStatus(NEvent::STATUS::ERR);
        }
        if(ev.getStatus()==NEvent::STATUS::ERR)
        {
            ev.setErr(NEvent::ERRNUM::READ_ERR);
            return;
        }
        ev.http->init(buf);
    }
    else if(ev.getStatus()==NEvent::STATUS::WAITSEND)
    {
        ev.http->sendData(ev.getFd());
        ev.updateTime();
    }
    else if(ev.getStatus()==NEvent::STATUS::ERR)
    {
        //log
        ep.removeFD(ev.getFd());
        fd_map[ev.getFd()] = nullptr;
        delete &ev;
    }
}

void NSub::Sub::removeEvent()
{
    for(auto & [fd,ev]:fd_map)
    {
        if(ev->timeOut())
        {
            ep.removeFD(ev->getFd());
            fd_map[ev->getFd()] = nullptr;
            delete &ev;
        }
    }
}

void NSub::Sub::start()
{
    while(true)
    {
        int i = addSubDo();
        if(!i)
        {
            removeEvent();
        }
    }
}