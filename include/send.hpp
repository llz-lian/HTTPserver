#pragma once
#include<http.h>
#include<server.h>
class SendHttp
{
private:
    /* data */
    Http * http;
    
    string file_name;
public:
    int clientfd;
    friend vector<string> *  getUri(const Http * http,string & file_name);
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
    
    inline string & getFileName(){
        return file_name;
    }
};

class Get:public SendHttp
{
private:
    /* data */
    struct stat status;
    vector<string> * cgi_args;
    bool is_static;
    void staticGet(int fd,const char * file_name,int file_size);
    void dynamicGet(int fd,const char * file_name);
public:
    virtual int sendData();
    Get(Http * http,int fd);
    virtual ~Get();
};
