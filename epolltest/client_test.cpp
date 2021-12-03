#include <sys/unistd.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
int main()
{
    char send_buf[] = "GET / HTTP1.1\r\nkeep-alive: true\r\n\r\n";

    int socfd = socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in addr;
    addr.sin_port = htons(8888);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = 0;

    int r = connect(socfd,(sockaddr *)&addr,sizeof(sockaddr));

    send(socfd,send_buf,strlen(send_buf),0);
    
    char buf[1024];
    recv(socfd,buf,strlen(buf),0);
    printf("%s\n start sleep\n",buf);

    sleep(10);
    printf("sleep over");
    close(socfd);
}