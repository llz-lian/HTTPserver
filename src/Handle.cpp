#include <string.h>
#include <unistd.h>   
#include <sys/mman.h>
#include <memory> 

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "Event.hpp"
#include "Handle.hpp"
#include "StaticNums.hpp"
using namespace std;
using PEvent = shared_ptr<NEvent::Event>;

void readData(Event::Event & ev,char * buf)
{
    int fd = ev.getFd();
    int read_num = 0;
    while ((read_num = read(fd,buf,sizeof(buf)))>0)
    {
        /* code */
    }
    if(read_num<0)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return;
        else
        {
            ev.changeStatus(NEvent::STATUS::ERR);
            return;
        }
    }
    ev.changeStatus(NEvent::STATUS::WAITSEND);
}


int writeFd(PEvent & ev,const char * buff,size_t len)
{
    int fd = ev->getFd();
    ssize_t written;
    size_t n = len;
    while(len>0)
    {
        if((written = write(fd,buff,len))<=0)
        {
            perror("<writeFd>write err");
            ev->changeStatus(NEvent::STATUS::ERR);
            if(errno == EINTR)
                written = 0;
            else
                return -1;
        }
        len -= written;
        buff += written;
    }
    ev->changeStatus(NEvent::STATUS::WAITREAD);
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
        return;
    }
    int len = lseek(filefd,0,SEEK_END);  
    char *addr = (char *) mmap(0, file_size, PROT_READ, MAP_PRIVATE,filefd, 0);
    close(filefd);
    return addr;
}

void sendFile(PEvent & ev,string & file_name)
{

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