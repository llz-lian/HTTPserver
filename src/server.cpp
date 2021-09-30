#include<server.hpp>
#include<http.hpp>


Server::Server()
{
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
    addr.sin_port = htons(PORT);
    memset(&(addr.sin_zero),0,sizeof(addr.sin_zero));

    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&i,sizeof(i));
    //bind
    if(bind(sockfd,(sockaddr*)&addr,sizeof(sockaddr))<0)
    {
        perror("bind error");
        exit(1);
    }
    printf("bind success.\n");
    //listen
    if(listen(sockfd,MAX_Q_NUM)<0)// queue
    {
        perror("listen error");
        exit(1);
    }
    printf("http now listening.\n");
}
Server::~Server()
{

}
void Server::startLoop(int fd)
{
    FD_ZERO(&block_read_fdset);
    max_fd = fd+1;
    int cnt = 0;
    for(;;)
    {
        
        BOA_FD_SET(fd,&block_read_fdset);
        if(select(max_fd+1,&block_read_fdset,nullptr,nullptr,nullptr)==-1)// 保险+1
        {
            printf("select");
            if(errno == EINTR)
            {
                printf("eintr");
                continue;
            }
                
            else if(errno != EBADF)
            {
                perror("<Server::startloop>select error.");
            }
        }
        cnt++;
        if(cnt>1000)
        {
            tp.restart();
            cnt = 0;
        }
        if(FD_ISSET(fd,&block_read_fdset))
        {
            tp.commit(&Server::processRequests,fd);
        }

    }
    cout<<"whaaaat??";
}
int Server::processRequests(int server_s)
{
    char * buff = new char[BUFFER_SIZE];
    memset(buff,0,sizeof(char)*BUFFER_SIZE);
    sockaddr_in clientADDR;
    int clientfd = readData(server_s,buff,clientADDR);
    if(clientfd<0)
    {
        perror("<Server::processRequests>readData error");
        return 0;
    }
    sinfo info(clientADDR);

    shared_ptr<Http> http = make_shared<Http>(string(buff),info);
    http->sendData(clientfd);
    delete[] buff;
    close(clientfd); 
    return 0;
}
void Server::startServer()
{
    //加信息
    startLoop(sockfd);
}

void Server::clientADDR(sockaddr_in & addr)
{
    char ip[32];
    inet_ntop(AF_INET,&addr.sin_addr,ip,sizeof(ip));
    this_thread::get_id();
    printf("client ip,port:[%s,%d].\n",ip,ntohs(addr.sin_port));
}

int Server::readData(int fd, char * buf, sockaddr_in & client_addr)
{
    size_t size=sizeof(struct sockaddr);
    int clientfd = accept(fd,(sockaddr*)&client_addr,(socklen_t*)&size);
    if(clientfd<0)
    {
        perror("<Server::readData>accept client error");
        return -1;
    }
    int read_num = read(clientfd,buf,BUFFER_SIZE);
    if(read_num<0)
    {
        if(errno == EINTR)
            read_num = 0;
        else
            return -2;
    }
    return clientfd;
}