#include <string.h>
#include <unistd.h>   
#include <sys/mman.h>
#include <memory> 

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "Handle.hpp"
#include "StaticNums.hpp"
using namespace std;

int readData(int fd,char * buf)
{
    int read_num = 0;
    while ((read_num = read(fd,buf,sizeof(buf)))>0)
    {
        /* code */
    }
    if(read_num<0)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return 0;
        else
        {
            return -1;
        }
    }
    return 1;
}


int writeFd(int fd,const char * buff,size_t len)
{
    ssize_t written;
    size_t n = len;
    while(len>0)
    {
        if((written = write(fd,buff,len))<=0)
        {
            perror("<writeFd>write err");
            if(errno == EINTR)
                written = 0;
            else
                return -1;
        }
        len -= written;
        buff += written;
    }
    return n;
}
void getFileType(const char * file_name,char * file_type)
{
    if(strstr(file_name,".html"))
        strcpy(file_type,"text/html");
    else if(strstr(file_name,".gif"))
        strcpy(file_type,"image/gif");
    else if(strstr(file_name,".jpg"))
        strcpy(file_type,"image/jpeg");
    else 
        strcpy(file_type,"text/plain");
}


char * Mmap(const char * file_name,uint file_size)
{
    int filefd;
    if((filefd = open(file_name,O_RDONLY,0))<0)
    {
        perror("<Get::staticGet>open");
        return nullptr;
    }
    int len = lseek(filefd,0,SEEK_END);  
    char *addr = (char *) mmap(0, file_size, PROT_READ, MAP_PRIVATE,filefd, 0);
    close(filefd);
    return addr;
}







/*
WAIT_READ   readData(req)--->READING---->WAIT_WRITE
READING     x
WAIT_WRITE  Sender.preparesend()-->writeFD()
WRITEING
WRITE_OVER
TIME_OUT    remove(event)
READ_ERROR  remove(event)
WRITE_ERROR x
ERROR       poccesserror()

*/