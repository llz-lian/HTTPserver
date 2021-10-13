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
};

class ConnectDB
{
private:
    connection c;
    MYSQL mysql;
    MYSQL_RES * res = nullptr;
    MYSQL_ROW row;
    MYSQL_RES * doSql(const char * sql,unsigned int len);
    template <class T,class ...Args>
    auto getInsertData(const T & t,const Args & ...args)->decltype(t.insertDB())
    {
        string ret = "";
        ret += t.insertDB();
        ret += getInsertData(args...);
        return ret;
    }
    inline string getInsertData()const{return "";};
public:
    ConnectDB();
    ConnectDB(ConnectDB & cdb);
    ~ConnectDB();
    void connectMysql();
    void searchDB(const char * sql,unsigned int len);

    template <class ...Args>
    void insertData(string & table,const Args & ...args){

        string sql = "insert into " + table;
        sql += getInsertData(args...);
        res = doSql(sql.c_str(),sql.length());
    };

    void showResult() const;
    void closeDB();

    void changeDB(const string &new_db);
    void changeUsr(const string &new_usr,const string &new_passwd);
};




int connectMysql(MYSQL & sql,connection & c) //throw(int)
{
    if(!mysql_real_connect(&sql,c.host_name.c_str()
    ,c.usr_name.c_str(),c.passwd.c_str(),c.database.c_str(),c.port,
    nullptr,0))
    {
        cout<<"connect failed!"<<endl;
        throw(-1);
    }
    cout<<"connected"<<endl;
    return 0;
}
MYSQL_RES * sqlQuery(MYSQL &sql,char * sql_q,unsigned int len) //throw(int)
{
    if(mysql_real_query(&sql,sql_q,len))
    {
        throw(0);
    }else
    {
        MYSQL_RES *res = mysql_store_result(&sql);
        if(res == nullptr)
        {
            throw(1);
        }
        return res;
    }
}
