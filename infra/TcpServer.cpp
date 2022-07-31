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
#define LEN 1024
int main(int argc, char const* argv[])
{
    TcpService service=TcpService();
    service.setPort(PORT);
    service.start();


    // int server_fd, new_socket, valread;
    // struct sockaddr_in address;
    // int opt = 1;
    // int addrlen = sizeof(address);
    // const char* hello = "server received the message";
  

    // tcpConnectionSocket masterSocket=tcpConnectionSocket();
    // masterSocket.setPort(PORT);
    // masterSocket.getReady();
    // tcpConnection temp=masterSocket.getConnectedSocket();

    // while(1){
    //     char inp[LEN]={0};
    //     temp.in(inp,LEN);
    //     printf("%s\n",inp);
    //     char out[LEN]="hello";
    //     temp.out(out);
    // }


    
  // closing the connected socket
    //close(new_socket);
  // closing the listening socket
    //shutdown(server_fd, SHUT_RDWR);
    return 0;
}