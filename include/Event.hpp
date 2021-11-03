#include <atomic>
#include "StaticNums.hpp"
#include "Timer.hpp"
class Timer;
namespace EVENT{
    enum{
            WAIT_READ,
            READING,
            WAIT_WRITE,
            WRITEING,
            TIME_OUT,
            ERROR
        };
    class BaseEvent
    {
    private:
        int fd;//文件描述符
        std::atomic_uint status = WAIT_READ;//状态
    public:
        unsigned int getStatus() const{return status;};
        void changeStatus(unsigned int status){this->status = status;};//叫set也行
        inline int getFd()const {return fd;};
        BaseEvent(int fd):fd(fd){};
        virtual ~BaseEvent();
    };
    class Event: public BaseEvent
    {
    private:
        Timer wait_time; //等待
        bool stop = true;//是否开始计时
        //并发处理 status
    public:
        Event(int fd):BaseEvent(fd){};
        virtual ~Event(){};
        void startRecord(){
            if(stop==false)
            {
                //重复调用
                return;
            }
            stop = false;
            auto timeout = [this]{
                /*
                    互斥条件
                */
               this->changeStatus(TIME_OUT);
            };
            wait_time.setTimeOut(timeout,NUMS::MAX_WAIT_TIME);
        };//开始计时
    };
    
    class SEvent: public BaseEvent
    {
    private:
    public:
        SEvent(int fd):BaseEvent(fd){};
        virtual ~SEvent(){};
    };
}
/*
    fd = accpet(fd)
    event(fd);
    Epoll.addepoll(event){
        ...
        dohandle(evnet);
    };


    dohandle(event){
        event.startRecord();

        switch(event.getStatus)
        {
            handle();
        }
        ...
        ...
        ...
    }

    handle(){
        readData(WAIT_READ){
            event.changeStatus()//reading
            ...
            read();
            ...
            event.changeStatus();//WAIT_WRITE
            return;
        }
        writeData(WAIT_WRITE){
            event.changeStatus();//writing
            ...
            write();
            ...
            ...
            event.changeStatus();//WAIT_READ
            return;
        }
        excpet(){
            event.changeStatus();//error
            ...
            write();
            ...
            event.changeStatus();//timeout
            return;
        }
        clearEvnet(){
            ~event();
        }
    }
    ~event(){
        close(fd);
        ...
        ...
    }
*/