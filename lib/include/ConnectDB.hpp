#include <mysql/mysql.h>
#include<string>
#include<string.h>
#include<stdio.h>
#include<iostream>
using namespace std;

struct connection
{
    /* data */
    string host_name="localhost";
    string usr_name = "llz";
    string passwd = "123456";
    string database = "CLIENT_LOG";
    int port = 3306;
    connection(){};
    connection(string &hn,string &un,string &pd,string &db,int p):
    host_name(hn),usr_name(un),passwd(pd),database(db),port(p)
    {
    }
    connection(const connection & c):
    host_name(c.host_name),usr_name(c.usr_name),passwd(c.passwd),database(c.database),port(c.port)
    {};
    const connection & operator=(const connection&c){
        return c;
    }
};

class ConnectDB
{
private:
    connection c;
    bool connected = false;
    MYSQL mysql;
    MYSQL_RES * res = nullptr;
    MYSQL_ROW row;
    MYSQL_RES * doSql(const char * sql,unsigned int len);
    template <class T,class ...Args>
    auto getInsertData(const T & t,const Args & ...args)->decltype(t.insertDB())
    {
        string ret = "";
        ret += t.insertDB();//类里实现string insertDB();
        ret += getInsertData(args...);
        return ret;
    }
    inline string getInsertData()const{return "";};
    ConnectDB(ConnectDB & cdb);
    string myerror(){return mysql_error(&mysql);};
public:
    ConnectDB(){mysql_init(&mysql);};
    ~ConnectDB(){
        if(connected)
        {
            closeDB();
        }
    };
    void connectMysql();
    void searchDB(const char * sql,unsigned int len);

    template <class ...Args>
    void insertData(string & table,const Args & ...args){
        //table 插入的表
        //args  插入的类
        string sql = "insert into " + table;
        sql += getInsertData(args...);
        res = doSql(sql.c_str(),sql.length());
    };

    void showResult();
    void closeDB(){
        if(connected)
        {
            mysql_close(&mysql);
            connected = false;
        }
    };

    inline void changeConnect(const connection & c){
        this->c = c;
    };
};
