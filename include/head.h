#pragma once
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>

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
using namespace std;

#define BOA_FD_SET(fd, where) { FD_SET(fd, where); \
    if (fd > max_fd) max_fd = fd; \
    }

const int MAX_LEN = 512;

int writeFd(int fd,char * buff,size_t len);
void getFileType(const char * file_name,char * file_type);
int readFile(const char * file_name,char * buff,int len);
