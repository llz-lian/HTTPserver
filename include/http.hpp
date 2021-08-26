#pragma once

#include<head.hpp>
class Http;
//vector<string> *  getUri(const Http * http,string & file_name);
shared_ptr<vector<string>> getUri(const Http * http,string & file_name);
class Http
{
private:
    /* data */
    const string * data;//请求报文整体
    int pos;//当前指针
    string http_ver;//版本
    string url;
    string method;//方法
    //string head_r;//
    const string * body;//本体
    enum methods{GET,POST,HEAD};
    map<string,string> header;
    //const int MAX_LEN = 512;
    void paser(const string & str);//解析报文
    void getHeader(const string &head,stringstream &ss);//解析请求头部
    void getLine(const string &line,stringstream &ss);//解析请求行
    void getBody(const string &&body);//得到请求本体
public:
    //friend vector<string> *  getUri(const Http * http,string & file_name);
    friend shared_ptr<vector<string>> getUri(const Http * http,string & file_name);
    friend class SendHttp;
    void show();

    void sendData(int fd);
    Http(const string & request);
    ~Http();
};

