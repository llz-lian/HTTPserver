#pragma once
#include <map>
#include <functional>
#include <memory>

#include "threadpool.hpp"
#include "Event.hpp"
#include "Handle.hpp"

namespace Epoll{
    using namespace std;
    using Event = shared_ptr<EVENT::Event>;
    using SEvent = shared_ptr<EVENT::SEvent>;

    using BaseE = shared_ptr<EVENT::BaseEvent>;
    class Epoll{
    private:
        unordered_map<BaseE,handle> todo;//fd <-> handle
        Epoll(const Epoll &e) = delete;
        int server_fd;
        bool active = true;

        threadpool tp;
        void handleIn();
        void addFd(int fd);
        void removeFD(int fd);//while(active){sleep(MAX_WAIT_TIME);reomve(fd)}
    public:
        Epoll();
        ~Epoll();
        void startLoop();
    };
}