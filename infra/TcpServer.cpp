#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "TcpConnectionSocket.h"
#include "TcpService.h"
#include "TcpConnection.h"
#include "GameService.h"
#include <iostream>
#define TCP_PORT 8080
#define UDP_PORT 8079
int main(int argc, char const* argv[])
{
    GameService gameservice=GameService();
    gameservice.setting(TCP_PORT,UDP_PORT);
    gameservice.start();

    // TcpService tcp=TcpService();
    // tcp.setPort(PORT);
    // tcp.setUdp(UDP_PORT);
    // tcp.start();

}