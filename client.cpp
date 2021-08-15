#include<sys/types.h>
#include<string.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>
#include<pthread.h>

#define PORT 6000
#define BUFFER_SIZE 1400
#define FILE_NAME_MAX 512

int main()
{
    int sockfd;
    hostent * host;
    sockaddr_in server_addr;
    if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket error");
        exit(1);
    }
    memset(&server_addr,0,sizeof(sockaddr_in));
    server_addr.sin_addr = *(in_addr*)gethostbyname("127.0.0.1")->h_addr_list[0];
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    memset(&server_addr.sin_zero,0,8);
    if(connect(sockfd,(sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        perror("connect error");
        exit(1);
    }
    char buff[BUFFER_SIZE] = "POST /passport/web/login HTTP/1.1\r\nHost: kyfw.12306.cn\r\nConnection: keep-alive\r\n Content-Length: 55\r\n Accept: application/json, text/javascript, */*; q=0.01\r\nOrigin: https://kyfw.12306.cn\r\nX-Requested-With: XMLHttpRequest\r\nUser-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.146 Safari/537.36\r\nContent-Type: application/x-www-form-urlencoded; charset=UTF-8\r\nReferer: https://kyfw.12306.cn/otn/login/init\r\nAccept-Encoding: gzip, deflate, br\r\nAccept-Language: zh-CN,zh;q=0.9,en;q=0.8\r\nCookie: _passport_session=0b2cc5b86eb74bcc976bfa9dfef3e8a20712; _passport_ct=18d19b0930954d76b8057c732ce4cdcat8137; route=6f50b51faa11b987e576cdb301e545c4; RAIL_EXPIRATION=1526718782244; RAIL_DEVICEID=QuRAhOyIWv9lwWEhkq03x5Yl_livKZxx7gW6_-52oTZQda1c4zmVWxdw5Zk79xSDFHe9LJ57F8luYOFp_yahxDXQAOmEV8U1VgXavacuM2UPCFy3knfn42yTsJM3EYOy-hwpsP-jTb2OXevJj5acf40XsvsPDcM7; BIGipServerpool_passport=300745226.50215.0000; BIGipServerotn=1257243146.38945.0000; BIGipServerpassport=1005060362.50215.0000\r\n\r\n username=balloonwj%40qq.com&password=iloveyou&appid=otn";
    int count = send(sockfd,buff,strlen(buff),0);
    if(count<0)
    {
        perror("send error");
        exit(1);
    }
    printf("sent %d byte\n",count);
    return 0;
}