#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<signal.h>
#include <wait.h>
#include<sys/ioctl.h>
#include<sys/epoll.h>
#include<unistd.h>
#include<netinet/in.h>
#include<errno.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#include "aux/threadpool.hpp"

namespace Server{
    using namespace std;
    class Server
    {
    private:
        /* data */
        Server(const Server &s) = delete;
        threadpool p;
        unsigned int port = 8888;
        int fd;
    public:
        Server(/* args */);
        ~Server();
    };
    
    Server::Server(/* args */)
    {

    }
    
    Server::~Server()
    {
    }
    void setNoBlock(int fd)
    {
        int flags = fcntl(fd,F_GETFL,0);
        flags |= O_NONBLOCK;
        flags |= O_NDELAY;
        int ret = fcntl(fd,F_SETFL,flags);
        return ret;
    }

    int getSockfd(unsigned int port)
    {
        int fd = 0;
        sockaddr_in addr;
        socklen_t len;
        if((fd = socket(AF_INET,SOCK_STREAM,0))<0)
        {
            perror("socket error");
            exit(1);
        }
        int opt = 1;
        if(setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt))<0)
        {
            perror("setsocket error");
            close(fd);
            exit(1);
        }
        
        //设置非阻塞
        setNoBlock(fd);

        //绑定地址端口
        memset(&addr,0,sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(port);

        if(bind(fd,(sockaddr *)&addr,sizeof(addr))<0)
        {
            perror("bind error");
            close(fd);
            exit(1);
        }

        if(listen(fd,1024)<0)
        {
            perror("listen error");
            close(fd);
            exit(1);
        }
        return fd;
    }


}