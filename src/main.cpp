#include "Server.hpp"


int main()
{
    NServer::Server server(16,1);
    server.start();
    return 0;
}