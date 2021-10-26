#pragma once
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
#include<unistd.h>
#include<netinet/in.h>
#include<errno.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#include<string>
#include<vector>
#include<map>
#include<iostream>
#include<sstream>
#include<thread>
#include<functional>

#include <memory>
#include"./aux/threadpool.hpp"
#include"./aux/TimeCtr.hpp"
using namespace std;

#define BOA_FD_SET(fd, where) { FD_SET(fd, where); \
    if (fd > max_fd) max_fd = fd; \
    }

const int MAX_LEN = 512;

int writeFd(int fd,const char * buff,size_t len);
void getFileType(const char * file_name,char * file_type);
int readFile(const char * file_name,char * buff,int len);

void * Mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset);

extern char **environ;