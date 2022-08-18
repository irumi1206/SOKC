#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "TcpConnectionSocket.h"
#include "TcpService.h"
#include "TcpConnection.h"
#include <iostream>
#define PORT 8080
#define UDP_PORT 8079
#define LEN 1024
int main(int argc, char const* argv[])
{
    TcpService service=TcpService();
    service.setPort(PORT);
    service.setUdp(UDP_PORT);
    service.start();
    return 0;
}