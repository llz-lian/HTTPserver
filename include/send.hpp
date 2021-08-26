#pragma once
#include<http.hpp>
#include<server.hpp>
class SendHttp
{
private:
    /* data */
    Http * http;
    
    string file_name;
    
public:
    int clientfd;
    friend shared_ptr<vector<string>>  getUri(const Http * http,string & file_name);
    virtual int sendData()=0;
    SendHttp(Http * Http,int clientfd,string name = "./pages")
    {
        this->clientfd = clientfd;
        this->http = http;
        file_name = name;
    }
    virtual ~SendHttp()
    {
        
    }
    void sendBad(int fd){
        char buf[Server::BUFFER_SIZE] = "Http/1.0 404 Not Found\r\n";
        if(sendHead(fd,buf)<0){
            perror("<Get::Get>sendHead");
        }
    }
    int sendHead(int fd,char * buf){
        if(writeFd(fd,buf,strlen(buf))!=strlen(buf))
        {
            perror("<SendHttp::sendHead>writeFd error");
            return -1;
        }    
        return 0;
    }
    inline string & getFileName(){
        return file_name;
    }
};

class Get:public SendHttp
{
private:
    /* data */
    struct stat status;
    shared_ptr<vector<string>> cgi_args = make_shared<vector<string>>();;
    bool is_static;
    void staticGet(int fd,const char * file_name,int file_size);
    void dynamicGet(int fd,const char * file_name);
public:
    virtual int sendData();
    Get(Http * http,int fd);
    virtual ~Get();
};


class Post:public SendHttp
{
private:
    vector<string> * args;
public:
    Post(Http * http,int fd):SendHttp(http,fd){

    };
    virtual int sendData(){
        return 0;
    };
    virtual ~Post(){};
};