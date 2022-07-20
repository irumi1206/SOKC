#include "tcpConnection.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

tcpConnection::tcpConnection(){
    tcpSocket=-1;
}

void tcpConnection::setTcpSocket(int socketDescriptor){
    tcpSocket=socketDescriptor;
}

void tcpConnection::in(char8_t* buffer,int len){
    int valread=read(tcpSocket,buffer,len);
}

void tcpConnection::out(char8_t* message){
    send(tcpSocket,message,std::char_traits<char8_t>::length(message),0);
}

