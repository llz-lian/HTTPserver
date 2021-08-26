#pragma once
#include<head.hpp>
class Server
{
private:
    /* data */
    sockaddr_in addr;
    const int MAX_Q_NUM = 50;
    const int PORT = 8888;
    int sockfd;
    int max_fd;
    fd_set block_read_fdset;
    static int processRequests(int server_s);
    static inline int readData(int fd,char * buf);
    static inline void clientADDR(sockaddr_in & adddr);
    threadpool tp{16};
public:
    static const int BUFFER_SIZE = 4096;

    Server(/* args */);
    void startServer();
    void startLoop(int fd);
    ~Server();
};