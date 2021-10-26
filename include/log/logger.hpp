#include "head.hpp"

class LogAdder;
class LogEvent;
class Logger;

struct Logstuff
{
    enum Level{
        DEBUG = 1,
        INFO,
        WARN,
        ERROR,
        FATAL
    };  
    using add_ptr = shared_ptr<LogAdder>;
    using evnt_ptr = shared_ptr<LogEvent>;
    using log_ptr = shared_ptr<Logger>;
};
class LogAdder{
public:
    LogAdder(Logstuff::Level level,Logstuff::evnt_ptr evnt);
    ~LogAdder();
private:
    Logstuff::Level level;
};
class LogEvent{
public:
    LogEvent();
    ~LogEvent();
    virtual void log(Logstuff::Level level) = 0;//void=0
private:
    const char * file_name = nullptr;
    unsigned int line = 0;
    unsigned int thread_id = 0;
    unsigned int time;
    string contnent;
};
class Logger
{
private:
    /* data */
    Logstuff::Level level;

public:
      
    Logger(const string name = "root");
    void addlog(Logstuff::Level evnt_lev,Logstuff::evnt_ptr evnt);
    ~Logger();
};