#include <functional>
#include <netinet/in.h>

#include "Event.hpp"
#include "Epoll.hpp"
using handle = std::function<void()>;


int readData(int fd,char * buf,sockaddr_in & client_addr);
int writeFd(int fd,const char * buff,size_t len);
void getFileType(const char * file_name,char * file_type);
void * Mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset);
