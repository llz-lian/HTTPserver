#pragma once
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "Send.hpp"
#include "factory.hpp"

using namespace std;
class Http;
//vector<string> *  getUri(const Http * http,string & file_name);
shared_ptr<vector<string>> getUri(shared_ptr<Http> http,string & file_name);
class Http:public enable_shared_from_this<Http>
{
private:
    /* data */
    const string * data;//请求报文整体
    int pos;//当前指针
    string http_ver;//版本
    string url;
    string method;//方法
    const string * body;//本体
    enum methods{GET,POST,HEAD};
    map<string,string> header;
    void paser(const string & str);//解析报文
    void getHeader(const string &head,stringstream &ss);//解析请求头部
    void getLine(const string &line,stringstream &ss);//解析请求行
    void getBody(const string &&body);//得到请求本体
public:
    //friend vector<string> *  getUri(const Http * http,string & file_name);
    shared_ptr<vector<string>> getUri(shared_ptr<Http> http,string & file_name);
    friend class NSend::SendHttp;
    void show() const;
    const string * postData(){
        return body;
    };
    shared_ptr<Http> getThis(){
        return shared_from_this();
    };
    inline const string & getUrl()
    {
        return url;
    }    
    void sendData(int fd);
    void init();
    Http(const string & request);
    ~Http();
};

