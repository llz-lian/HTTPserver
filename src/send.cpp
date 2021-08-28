#include<send.hpp>
#include<string>
Get::Get(shared_ptr<Http> http,int fd):SendHttp(http,fd)
{
    try
    {
        /* code */
        cgi_args = getUri(http,getFileName());
        is_static = cgi_args->size()==0;
        
        /*char buf[80];   
        getcwd(buf,sizeof(buf));   
        printf("current working directory: %s\n", buf);   */
        if(stat(getFileName().c_str(),&status)<0||http==nullptr)
        {       //add http
            throw string("<Get::Get>no such file.");
        }
    }
    catch(const std::string& e)
    {
        std::cerr << e << '\n';
        status.st_size = 0;
        sendBad(fd);
    }
    
}
Get::~Get()
{
    
}
int Get::sendData()
{
    if(status.st_size<=0)
        return -1;
    if(is_static)
        staticGet(clientfd,getFileName().c_str(),status.st_size);
    else
        dynamicGet(clientfd,getFileName().c_str());
    return 0;
}

void Get::staticGet(int fd,const char * file_name,int file_size)
{
    char * send_html,file_type[MAX_LEN],buf[Server::BUFFER_SIZE];
    getFileType(getFileName().c_str(),file_type);
    sprintf(buf,"Http/1.0 200 OK\r\n");
    sprintf(buf,"%sServer:my web server\r\n",buf);
    sprintf(buf,"%sContent-length:%d\r\n",buf,file_size);
    sprintf(buf,"%sContent-type:%s\r\n\r\n",buf,file_type);
    
    if(sendHead(fd,buf)<0)
    {
        perror("<Get::staticGet>sendHead");
        return;
    }
    /*mmap*/
    int filefd;
    if((filefd = open(file_name,O_RDONLY,0))<0)
    {
        perror("<Get::staticGet>open");
        return;
    }
    int len = lseek(filefd,0,SEEK_END);  
    char *addr = (char *) mmap(0, file_size, PROT_READ, MAP_PRIVATE,filefd, 0);
    close(filefd);
/*
    if(readFile(file_name,buf,Server::BUFFER_SIZE)<0)
    {
        perror("<Get::staticGet>read error");
        return;
    }
*/
    if(writeFd(fd,addr,file_size)!=file_size)
    {
        printf("%s\n",file_name);
        cout<<getUrl();
        perror("<Get::staticGet>writeFd error");
        return;
    }
}

void Get::dynamicGet(int fd,const char * file_name)
{
    if(cgi_args->size()<2)
    {
        perror("<Get::dynamicGet>cgiargs error");
        return;
    }
    char * send_html,file_type[MAX_LEN],buf[Server::BUFFER_SIZE];
    getFileType(getFileName().c_str(),file_type);
    sprintf(buf,"Http/1.0 200 OK\r\n");
    sprintf(buf,"%sServer:my web server\r\n",buf);
    sprintf(buf,"%sContent-type:%s\r\n\r\n",buf,file_type);
    
    if(sendHead(fd,buf)<0)
    {
        perror("<Get::dynamicGet>sendHead");
        return;
    }
    //cout<<"cgi-args:"<<(*cgi_args)[0]<<" "<<(*cgi_args)[1]<<endl;
    char * list[] = {const_cast<char *>((*cgi_args)[0].c_str()),const_cast<char *>((*cgi_args)[1].c_str()),(char *)0};

    int pid = fork();

    if(pid == 0)
    {
        if(dup2(fd,STDOUT_FILENO)<0)
        {
            perror("<Get::dynamicGet>dup2");
            return;
        }    
        if(execve((*cgi_args)[0].c_str(),list,environ)<0)
        {
            perror("<Get::dynamicGet>execve");
            return;
        }
    }
    else
    {
        if (wait(NULL) < 0)
        {
            perror("<Get::dynamicGet>wait");
        }
    }
    return;
}



Post::Post(shared_ptr<Http> http,int fd):SendHttp(http,fd),post_body(http->postData())
{
    cgi_args = getUri(http,getFileName());
    try
    {
        if(stat(getFileName().c_str(),&status)<0||http==nullptr)
        {       //add http
            throw string("<Get::Get>no such file.");
        }
    }
    catch(const std::string& e)
    {
        std::cerr << e << '\n';
        status.st_size = 0;
        sendBad(fd);
    }
}

int Post::sendData()
{
    if(status.st_size<=0)
        return -1;
    char buf[Server::BUFFER_SIZE];
    sprintf(buf, "HTTP/1.1 200 OK\r\n"); 
    sprintf(buf,"%sServer:my web server\r\n",buf);
    if(sendHead(clientfd,buf)<0)
    {
        perror("<Post::sendData>sendHead");
        return -1;
    }
    //获得长度大小
    const map<string,string> & m = getMap();
    auto c = m.find("Content-Length");
    string conlen = c->second;
    int len = atoi(conlen.c_str());
    //临时文件
    char tempfile[] = {"post-temp.XXXXXX"};
    int tempfd = mkstemp(tempfile);
    if(tempfd<0)
    {
        perror("<Post::sendData>temp file");
        return -1;
    }
    //设置环境变量，方便cgi程序获取
    char len_buf[32] = {0};
    sprintf(len_buf, "CONTENT_LENGTH=%d",len);
    putenv(len_buf);
    //post数据写入文件
    if(writeFd(tempfd,post_body->c_str(),len)<0)
    {
        perror("<Post::sendData>write error");
        return -1;
    }
    //创建管道
    int pipes[2] = {};
    if(pipe(pipes) == -1)
    {
        perror("<Post::sendData>pipe create");
        return -1;
    }
    //fork
    int pid = fork();
    if(pid == 0)
    {
        if (dup2(pipes[1], STDOUT_FILENO) == -1) 
        {
            close(pipes[1]);
            perror("<Post::sendData>dup2 error");
            exit(-1);
        }
        close(pipes[1]);
        lseek(tempfd, SEEK_SET, 0);
        dup2(tempfd, STDIN_FILENO);
        close(tempfd);
        if (execve((*cgi_args)[0].c_str(), nullptr, environ) < 0)
        {
            perror("<Post::sendData>execve");
            exit(-1);
        }
    }
    else
    {
        close(tempfd);
        close(pipes[1]);

    }



    //char * list[] = {const_cast<char *>((*cgi_args)[0].c_str()),const_cast<char *>(post_body->c_str()),nullptr};


    return 0;
}