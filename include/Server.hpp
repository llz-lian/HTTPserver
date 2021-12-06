#include <vector>
#include "threadpool.hpp"
#include "factory.hpp"
#include "Sub.hpp"

namespace NServer{
    using namespace std;
    class Server
    {
    public:
        Server(int thread_num,int sub_num);
        ~Server();
        void start();
    private:
        int listen_fd;
        NEpoll::Epoll ep;
        threadpool addsub;
        vector<NSub::Sub *> subs;

        sockaddr_in addr;
        int sub_num;
        int next_sub = 0;
        void accpetFd();
        bool stop;
    };
}