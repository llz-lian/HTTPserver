#pragma once
#include<head.h>
class Server
{
private:
    /* data */
    sockaddr_in addr;
    const int MAX_Q_NUM = 5;
    const int PORT = 8888;
    int sockfd;
    int max_fd;
    fd_set block_read_fdset;
    int processRequests(int server_s);



public:
    static const int BUFFER_SIZE = 4096;

    Server(/* args */);
    void clientADDR(sockaddr_in & adddr);
    void startServer();
    void startLoop(int fd);
    ~Server();
};