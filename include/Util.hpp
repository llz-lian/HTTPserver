#pragma once
#include <sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

#include<errno.h>
#include <memory.h>
#include <stdio.h>
#include "StaticNums.hpp"
/*
    read()
    write()

    setnonblock()
    getListenfd()

*/




void setNonBlockfd(int fd)
{
    int flags = fcntl(fd,F_GETFL,0);
    fcntl(fd,F_SETFL,flags|O_NONBLOCK);
};

int getListenfd(sockaddr_in & addr)
{
    int sockfd;
    int sin_size = sizeof(sockaddr);
    int i = 1;
    if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket error");
        exit(1);
    }
    printf("socket id = %d.\n",sockfd);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(NUMS::PORT);
    memset(&(addr.sin_zero),0,sizeof(addr.sin_zero));

    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&i,sizeof(i));
    setNonBlockfd(sockfd);

    //bind
    if(bind(sockfd,(sockaddr*)&addr,sizeof(sockaddr))<0)
    {
        perror("bind error");
        exit(1);
    }
    printf("bind success.\n");
    //listen
    if(listen(sockfd,NUMS::MAX_Q_NUM)<0)// queue
    {
        perror("listen error");
        exit(1);
    }
    printf("http now listening.\n");
    return sockfd;
};