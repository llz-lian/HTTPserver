#include "./include/Server.hpp"


int main()
{
    NServer::Server server(16,10);
    server.start();
    return 0;
}