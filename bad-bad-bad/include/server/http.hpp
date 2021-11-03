#pragma once

#include<head.hpp>
#include<info.hpp>
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

    sinfo & info;

    void paser(const string & str);//解析报文
    void getHeader(const string &head,stringstream &ss);//解析请求头部
    void getLine(const string &line,stringstream &ss);//解析请求行
    void getBody(const string &&body);//得到请求本体
public:
    //friend vector<string> *  getUri(const Http * http,string & file_name);
    friend shared_ptr<vector<string>> getUri(shared_ptr<Http> http,string & file_name);
    friend class SendHttp;
    void show() const;
    inline void showInfo() const
    {
        info.show();
    };
    
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

    Http(const string & request,sinfo & in):info(in)
    {
        data = &request;
        paser(request);
        pos = 0;
        info.setUrl(url);
    };
    ~Http();
};

