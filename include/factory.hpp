#pragma once
#include <send.hpp>
#include <string>
#include <functional>
using namespace std;
class Factory{
public:
    template<class T>
    struct register_
    {
        register_(const string & s)
        {
            Factory::get().map_.emplace(s,[]{return new T();});
        }
        /* data */
        template<class ...Args>
        register_(const string & t,Args ...args)
        {
            Factory::get().map_.emplace(t,[&]{return new T(args...);});
        }
    };
    static SendHttp* getSender(const string & s)
    {
        if(map_.find(s)==map_.end())
            throw "no such method\n";
        return Factory::get().map_[s]();
    }
    static std::shared_ptr<SendHttp> produce_shared(const std::string& key)
    {
        auto & a = map_;
        return std::shared_ptr<SendHttp>(getSender(key));
    }
private:
    Factory(){};
    ~Factory(){};

    static Factory & get()
    {
        static Factory fac;
        return fac;
    }

    Factory(const Factory &) = delete;
    Factory(Factory &&) = delete;
    static map<string,function<SendHttp* ()>> map_;
};

map<string,function<SendHttp* ()>> Factory::map_;
inline void registSender()
{
    Factory::register_<Get>("GET");
    Factory::register_<Post>("POST");
}
