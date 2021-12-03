#include <map>
#include <vector>

#include "Epoll.hpp"
#include "threadpool.hpp"
#include "Event.hpp"
namespace NSub
{
    using namespace std;
    class Sub
    {
    public:
        Sub();
        ~Sub();
        void start();
        NEpoll::Epoll ep;
    private:
        const int MAX_FD = 300;
        threadpool doit;
        vector<epoll_event> ep_events;
        map<int,NEvent::Event *> map;

        void removeEvent();
        void addMap(int fd);
        int addSubDo();
        void processing(NEvent::Event &ev,uint flags);
    };
}