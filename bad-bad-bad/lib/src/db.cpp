#include "../include/ConnectDB.hpp"

void ConnectDB::connectMysql()
{
    if(!mysql_real_connect(&mysql,c.host_name.c_str()
    ,c.usr_name.c_str(),c.passwd.c_str(),c.database.c_str(),c.port,
    nullptr,0))
    {
        //error
        cout<<"connect error"<<myerror()<<endl;
        return;
    }
    //connect
    connected = true;
}

MYSQL_RES * ConnectDB::doSql(const char * sql,unsigned int len)
{
    //mysql_query(&mysql,"set names gbk;");
    if(mysql_real_query(&mysql,sql,len))
    {
        //error
        cout<<"dosql error!"<<myerror()<<endl;
    }
    else
    {
        //success
        if(!(res = mysql_store_result(&mysql)))
        {
            //error
        }
        else
        {
            return res;
        }
    }
    return nullptr;
}

void ConnectDB::showResult()
{
    cout<<"line affected:"<<mysql_affected_rows(&mysql)<<endl;
    if(res == nullptr)
    {
        //error
        return;
    }
    while(row = mysql_fetch_row(res))
    {
        for(int t = 0;t<mysql_num_fields(res);t++)
        {
            cout<<row[t]<<" ";
        }
        cout<<"........................"<<endl;
    }
    mysql_free_result(res);
}

void ConnectDB::searchDB(const char *sql,unsigned int len)
{
    res = doSql(sql,len);
    showResult();
}
