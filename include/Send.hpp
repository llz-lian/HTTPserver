#pragma once
#include<sys/stat.h>

#include "Http.hpp"
#include "Event.hpp"
#include "StaticNums.hpp"

namespace Send{
using namespace HTTP;
using PEvent = shared_ptr<EVENT::Event>;
enum{
    SEND_HEAD,
    SEND_BODY
};
class Sender{
private:
    string file_name;
public:
    PEvent & ev;
    shared_ptr<Http> http;

    friend shared_ptr<vector<string>>  getUri(shared_ptr<Http> http,string & file_name);
    virtual string prepareSend()=0;
    Sender(shared_ptr<Http> & http,PEvent & ev,string file_name):http(http),ev(ev),file_name(file_name){};
    virtual ~Sender(){};

    string prepareHead();
    string prepareBad();

    inline string & getFileName() {return file_name;};
    inline const string & getUrl(){return http->getUrl();};
    
    virtual inline void init(shared_ptr<Http> http,PEvent & event)
    {
        this->http = http;
        this->ev = event;
    }
};
class Get:public Sender{
private:
    struct stat file_status;
    shared_ptr<vector<string>> cgi_args = make_shared<vector<string>>();
    string pStatic();
    string pDynamic();
    string SendHead();
    string SendBody();
public:
    virtual string prepareSend();
    Get & operator=(const Get &get){
        this->ev = move(get.ev);
        this->http = move(get.http);
        this->cgi_args = move(get.cgi_args);
        this->file_status = get.file_status;
    };
    Get(shared_ptr<Http> & http,PEvent & ev);
    virtual inline void init(shared_ptr<Http> & http,PEvent & ev)
    {
        *this = Get(http,ev);
    }
};

}