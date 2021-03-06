#pragma once
#include <string>
#include <string.h>
#include<sys/stat.h>

#include "Http.hpp"
#include "Handle.hpp"
#include "StaticNums.hpp"
//.cpp内实现
class Http;
namespace NSend{
    using namespace std;
class SendHttp
{
private:
    /* data */
    shared_ptr<::Http> http;

    string file_name;
public:
    int clientfd;
    friend shared_ptr<vector<string>>  getUri(shared_ptr<::Http> http,string & file_name);
    virtual int sendData()=0;
    SendHttp(string name = "./pages")
    {
        file_name = name;
    }
    SendHttp(shared_ptr<::Http> http,int clientfd,string name = "./pages")
    {
        this->clientfd = clientfd;
        
        this->http = http;
        file_name = name;
    }
    virtual ~SendHttp()
    {
        
    }
    void sendBad(int fd){
        char buf[NUMS::MAX_BUFF] = "Http/1.0 404 Not Found\r\n";
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
    };
    inline string & getFileName(){
        return file_name;
    };

    virtual inline void init(shared_ptr<::Http> http,int clientfd)
    {
        this->http = http;
        this->clientfd = clientfd;
    };
    inline string & getUrl();
    inline const map<string,string> &getMap();
};

class Get:public SendHttp
{
private:
    /* data */
    struct stat status;
    shared_ptr<vector<string>> cgi_args = make_shared<vector<string>>();
    bool is_static;
    void staticGet(int fd,const char * file_name,int file_size);
    void dynamicGet(int fd,const char * file_name);
public:
    virtual int sendData();
    Get(){};
    Get(shared_ptr<::Http> http,int fd);
    virtual ~Get(){};
    virtual inline void init(shared_ptr<::Http> http,int fd){
        *this = Get(http,fd);
    };
};


class Post:public SendHttp
{
private:
    shared_ptr<vector<string>> cgi_args = make_shared<vector<string>>();
    const string * post_body;
    struct stat status;
public:
    Post(){};
    Post(shared_ptr<::Http> http,int fd);

    virtual inline void init(shared_ptr<::Http> http,int fd){
        *this = Post(http,fd);
    }
    virtual int sendData();
    virtual ~Post(){};
};
}