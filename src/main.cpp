#include "server.hpp"
#include "../lib/include/ConnectDB.hpp"
int main()
{    
    ConnectDB db;
    Server server;
    server.startServer();
    cout<<"ooops";
    return 0;
}