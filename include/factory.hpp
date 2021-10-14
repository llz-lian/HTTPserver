#pragma once
#include"head.hpp"
#include "send.hpp"
using namespace std;
class Factory{
public:
    template<class T>
    struct register_
    {
        register_(const string & s)
        {
            Factory::get().map_.emplace(s,&register_<T>::create);
        }
        /* data */
        template<class ...Args>
        register_(const string & t,Args ...args)
        {
            Factory::get().map_.emplace(t,[&]{return new T(args...);});
        }
        inline static SendHttp * create(){return new T;};
    };
    SendHttp* getSender(const string & s)
    {
        if(map_.find(s)==map_.end())
            throw "no such method\n";
        return map_[s]();
    }
    std::shared_ptr<SendHttp> produce_shared(const std::string& key)
    {
        return std::shared_ptr<SendHttp>(getSender(key));
    }
    inline static Factory & get()
    {
        static Factory fac;
        return fac;
    }
private:
    Factory(){};
    ~Factory(){};


    Factory(const Factory &) = delete;
    Factory(Factory &&) = delete;

    
    map<string,function<SendHttp* ()>> map_;
};

inline void registSender()
{
    Factory::register_<Get>("GET");
    Factory::register_<Post>("POST");
}
