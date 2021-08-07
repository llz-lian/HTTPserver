#include<send.h>

Get::Get(Http * http,int fd):SendHttp(http,fd)
{
    cgi_args = new vector<string>;
    cgi_args = getUri(http,getFileName());
    is_static = cgi_args->size()==0;
    cout<<getFileName()<<endl;
    if(stat(getFileName().c_str(),&status)<0)
    {       //add http
        char buf[Server::BUFFER_SIZE] = "Http/1.0 404 Not Found\r\n";
        writeFd(fd,buf,strlen(buf));
        
        perror("<Get::Get>stat");
    }
}
Get::~Get()
{
    delete cgi_args;
}
int Get::sendData()
{
    if(status.st_size<=0)
        return -1;
    if(is_static)
        staticGet(clientfd,getFileName().c_str(),status.st_size);
    else
        dynamicGet(clientfd,getFileName().c_str());
}

void Get::staticGet(int fd,const char * file_name,int file_size)
{
    char * send_html,file_type[MAX_LEN],buf[Server::BUFFER_SIZE];
    getFileType(getFileName().c_str(),file_type);
    sprintf(buf,"Http/1.0 200 OK\r\n");
    sprintf(buf,"%sServer:my web server\r\n",buf);
    sprintf(buf,"%sContent-length:%d\r\n",buf,file_size);
    sprintf(buf,"%sContent-type:%s\r\n\r\n",buf,file_type);
    
    if(writeFd(fd,buf,strlen(buf))!=strlen(buf))
    {
        perror("<Get::staticGet>writeFd error");
        return;
    }    

    if(readFile(file_name,buf,Server::BUFFER_SIZE)<0)
    {
        perror("<Get::staticGet>read error");
        return;
    }

    if(writeFd(fd,buf,strlen(buf))!=strlen(buf))
    {
        perror("<Get::staticGet>writeFd error");
        return;
    }
}

void Get::dynamicGet(int fd,const char * file_name)
{

}