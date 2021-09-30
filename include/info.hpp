#include"head.hpp"
class sinfo{
private:
    char ip[32] = {};
    uint port = 0;
    thread::id tid;
    string url;
public:
    sinfo(const sockaddr_in & addr):tid(this_thread::get_id()){
        inet_ntop(AF_INET,&addr.sin_addr,ip,sizeof(ip));
        port = ntohs(addr.sin_port);
    }
    void setUrl(const string & url)
    {
        this->url = url;
    }
    ~sinfo(){};
    inline void show() const
    {
        cout<<"@thread id:"<<tid<<endl<<"ip:"<<ip<<endl<<"port:"<<port<<endl;
        cout<<"url:"<<url<<endl;
    }
};