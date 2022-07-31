#include "TcpConnection.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

TcpConnection::TcpConnection(){
    tcpSocket=-1;
}

void TcpConnection::setTcpSocket(int socketDescriptor){
    tcpSocket=socketDescriptor;
}

void TcpConnection::in(char* buffer,int len){
    int valread=read(tcpSocket,buffer,len);
}

void TcpConnection::out(char* message){
    send(tcpSocket,message,strlen(message),0);
    //std::char_traits<char8_t>::length(message)
}

