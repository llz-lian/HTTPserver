#include <functional>
#include "Event.hpp"
#include "Epoll.hpp"
using handle = std::function<void()>;
class Core
{
public:
    void doit(Epoll::Event & e);//read() prasehttp() senddata()
    void doit(Epoll::SEvent & se);//read() addFd() startRecord()  prasehttp() senddata()
    virtual void doit() = 0;
    handle getHandle(Epoll::BaseE & e);
    void read();
    void write();
    void last();
    void error();
};