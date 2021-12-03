#include "Sub.hpp"

NSub::Sub::Sub():ep(MAX_FD)
{
    ep_events.resize(MAX_FD);
};

void NSub::Sub::addMap(int fd)
{
    if(fd<0)
        return;
    map[fd] = new Event::Event(fd);
}

int NSub::Sub::addSubDo()
{
    int num = ep.wait(ep_events);
    for(int i = 0;i<num;i++)
    {
        int fd = ep_events[i].data.fd;
        int event = ep_events[i].events;
        if(map.find(fd)==map.end())
        {
            addMap(fd);
        }
        doit.commit([&]{
            processing(*map[fd],event);
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
        readData(ev,buf);
        if(ev.getStatus()==NEvent::STATUS::ERR)
        {
            ev.setErr(NEvent::ERRNUM::READ_ERR);
            return;
        }
        ev.http->init();
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
        map[ev.getFd()] = nullptr;
        delete &ev;
    }
}

void NSub::Sub::removeEvent()
{
    for(auto & [fd,ev]:map)
    {
        if(ev->timeOut())
        {
            ep.removeFD(ev->getFd());
            map[ev->getFd()] = nullptr;
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